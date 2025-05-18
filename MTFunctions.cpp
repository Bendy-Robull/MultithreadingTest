#include "pch.h"
namespace MTFunctions
{

void filelogThreadFunction() {
	InstrumentationTimer timers("File Logger Thread Scope");
	std::unique_lock lock(queue_mutex);
	{
		std::scoped_lock<std::mutex> scopedCoutLock(cout_mutex);
		std::cout << "File log thread started\n";
	}
	while (true) {
		cv.wait(lock, [] { return !fileLogQueue.empty() || done; });
		while (!fileLogQueue.empty()) {

			auto log = fileLogQueue.front();
			fileLogQueue.pop();
			lock.unlock();
			std::ofstream file(log.name);

			{
				std::scoped_lock<std::mutex> scopedCoutLock(cout_mutex);
				std::cout << "Writing to file " << log.name << "\n";
			}

			if (file.is_open()) {
				file << log.fileData;
			}

			file.close();
			lock.lock();
		}
		if (done && fileLogQueue.empty()) break;
	}
	{
		std::scoped_lock<std::mutex> scopedCoutLock(cout_mutex);
		std::cout << "File log thread finished\n";
	}
}
void signalDone() {
	{
		std::scoped_lock<std::mutex> lock(queue_mutex);
		done = true;
	}
	cv.notify_all();
}


void threadFunction(std::latch& l, std::shared_ptr<Engine::PerlinNoiseGenerator> perlin, int i, std::vector<Project::Components::Chunk>& chunks) {

	std::string timerS = std::format("Chunk {} Creator Thread Scope", i); // Use std::format instead of concatenation

	InstrumentationTimer timer(timerS.c_str());

	std::ostringstream oss;

	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	std::tm now_tm;
#if defined(_WIN32) || defined(_WIN64)
	localtime_s(&now_tm, &now_time); // Use thread-safe localtime_s on Windows
#else
	localtime_r(&now_time, &now_tm); // Use thread-safe localtime_r on POSIX systems
#endif

	oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << " - Thread " << i << " started\n";

	Project::Components::Chunk chunk(i, LMath::LVector3(static_cast<float>(i % 3), 0, static_cast<float>(i / 3)), perlin);


	now = std::chrono::system_clock::now();
	now_time = std::chrono::system_clock::to_time_t(now);
#if defined(_WIN32) || defined(_WIN64)
	localtime_s(&now_tm, &now_time); // Use thread-safe localtime_s on Windows
#else
	localtime_r(&now_time, &now_tm); // Use thread-safe localtime_r on POSIX systems
#endif

	oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << " - Thread " << i << " finished\n";

	// Output the buffer to std::cout
	{
		std::scoped_lock<std::mutex> scopedCoutLock(cout_mutex); // Renamed variable to avoid shadowing
		chunks.push_back(chunk);
		std::cout << oss.str();
	}
	l.count_down();
}

void testThreadFunction()
{
	std::ostringstream oss;
    auto calculateFactorial = [](int n) -> std::vector<int> {
        std::vector<int> result(1, 1); // Initialize with 1

        for (int i = 2; i <= n; ++i) {
            int carry = 0;
            for (auto& digit : result) {
                int product = digit * i + carry;
                digit = product % 10;
                carry = product / 10;
            }
            while (carry) {
                result.push_back(carry % 10);
                carry /= 10;
            }
        }

        return result;
    };

    int number = 16;
    std::vector<int> factorial = calculateFactorial(number);

	oss << "Factorial of " << number << " is:\n";
    for (auto it = factorial.rbegin(); it != factorial.rend(); ++it) {
		oss << *it;
    }
	oss << std::endl;

	{
		std::scoped_lock<std::mutex> scopedCoutLock(cout_mutex); // Renamed variable to avoid shadowing
		std::cout << oss.str();
	}
	//MTFunctions::signalDone();

}
}