#pragma once


class FunctionThread
{
public:
	FunctionThread() = default;
	~FunctionThread()
	{
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_stop = true;
		}
		m_condition.notify_all();
		//std::for_each(m_threads.begin(), m_threads.end(), [](auto thread) {thread->join(); });
		m_thread.join();
	}
	void start()
	{
		m_thread = std::jthread([this]() {
			while (true)
			{
				std::function<void()> task;
				{
					std::unique_lock<std::mutex> lock(m_mutex);
					m_condition.wait(lock, [this] { return m_stop || !m_tasks.empty(); });
					if (m_stop && m_tasks.empty())
						return;
					task = std::move(m_tasks.front());
					//m_threads.emplace_back(std::make_unique<std::jthread>(task));
					m_tasks.pop();
				}
				task();
			}
			});
	}
	void enqueue(std::function<void()> task)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_tasks.push(std::move(task));
		lock.unlock();
		m_condition.notify_one();
	}

	void stop() {
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_stop = true;
		}
	}

private:
	//std::vector<std::unique_ptr<std::jthread>> m_threads;
	std::jthread m_thread;
	std::queue<std::function<void()>> m_tasks;
	std::mutex m_mutex;
	std::condition_variable m_condition;
	bool m_stop = false;

};

