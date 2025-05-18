#pragma once


#define CHUNK_SIZE 256
#define CHUNK_HEIGHT 128
#define FIXED_HEIGHT 64

#define CreateChunkLog true



namespace MTFunctions
{
	struct FileLog {
		std::string name;
		std::string fileData;

		FileLog(const FileLog& other) = default;
		FileLog(std::string& name, std::string& fileData) : name(name), fileData(fileData) {}
	};
	inline std::queue<FileLog> fileLogQueue;
	inline std::mutex cout_mutex;
	inline std::mutex queue_mutex;
	inline std::condition_variable cv;
	inline bool done = false;
	

	void filelogThreadFunction();
	void signalDone();

	void threadFunction(std::latch& l, std::shared_ptr<Engine::PerlinNoiseGenerator> perlin, int i, std::vector<Project::Components::Chunk>& chunks);


	void testThreadFunction();
}