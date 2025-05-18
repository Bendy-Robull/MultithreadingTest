
#include "pch.h"
void run();

int main()
{
	Instrumentor::Get().BeginSession("Multithreading Test");
	run();
	Instrumentor::Get().EndSession();

	return 0;
}

void run() {
	InstrumentationTimer timer("Main Scope");
	std::latch l(9);

	auto perlinGenerator = std::make_shared<Engine::PerlinNoiseGenerator>(0.50, 5.00, 16.00, 1, 1);
	std::cout << "Hello World!\n";
	std::vector<std::jthread> threads;
	std::vector<Project::Components::Chunk> chunks;
	FunctionThread functionThread;
	functionThread.start();
	chunks.reserve(9);
	threads.reserve(1);
	threads.emplace_back(MTFunctions::filelogThreadFunction);

	functionThread.enqueue(MTFunctions::testThreadFunction);


		//This is the test for parallel Chunk Creation
	for (int i = 0; i < 9; i++)
	{

		threads.emplace_back(MTFunctions::threadFunction, std::ref(l), perlinGenerator, i, std::ref(chunks));

		auto now = std::chrono::system_clock::now();

		std::time_t now_time = std::chrono::system_clock::to_time_t(now);

		std::tm now_tm;
#if defined(_WIN32) || defined(_WIN64)
		localtime_s(&now_tm, &now_time); // Use thread-safe localtime_s on Windows
#else
		localtime_r(&now_time, &now_tm); // Use thread-safe localtime_r on POSIX systems
#endif

		std::cout << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << " - Thread " << i << " created\n";
	}


	l.wait();
	functionThread.stop();
	MTFunctions::signalDone();
	std::cout << "All threads finished\n";
}
