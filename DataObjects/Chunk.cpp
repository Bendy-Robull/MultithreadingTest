#include "../pch.h"
namespace Project::Components {


	Chunk::Chunk(int idx, const LMath::LVector3& pos, std::shared_ptr<Engine::PerlinNoiseGenerator> perlinGenerator)
	{
		InstrumentationTimer timer("Chunk Constructor Scope");
		m_blocks = std::vector<std::vector<std::vector<Block>>>(128);
		for (int x : std::ranges::iota_view{ 0,128 }) {
			m_blocks[x] = std::vector<std::vector<Block>>(256);
			for (int y : std::ranges::iota_view{ 0,256 }) {
				m_blocks[x][y] = std::vector<Block>(128);
				for (int z : std::ranges::iota_view{ 0,128 }) {
					m_blocks[x][y][z] = Block();
					m_blocks[x][y][z].pos = 0 | (x << 16) | (y << 8) | (z << 0);
				}
			}
		}

		// Parallelize the height setting loop using thread-local vectors
		std::for_each(std::execution::par, std::views::iota(0, 128).begin(), std::views::iota(0, 128).end(), [&](int x) {
			std::vector<std::vector<Block>> local_blocks(256, std::vector<Block>(128));
			for (int z : std::ranges::iota_view{ 0,128 }) {
				int maxHeight = perlinGenerator->GetIntHeight((pos.X() + static_cast<float>(x)) * 0.01f, (pos.Z() + static_cast<float>(z)) * 0.01f);
				for (int y : std::ranges::iota_view{ 0,maxHeight }) {
					local_blocks[y][z].type = STONE;
				}
			}
			// Copy local_blocks to m_blocks
			for (int y = 0; y < 256; ++y) {
				for (int z = 0; z < 128; ++z) {
					m_blocks[x][y][z].type = local_blocks[y][z].type;
				}
			}
			});

		CreateMesh(idx);


	}


	void Chunk::CreateMesh(int idx) {
		InstrumentationTimer timer("Chunk Creation Scope - CreateMesh");
		UINT id = 0;
		for (const auto& [x, y, z] : std::views::cartesian_product(std::views::iota(0, 128),
			std::views::iota(0, 256),
			std::views::iota(0, 128))) {
			if (m_blocks[x][y][z].type == STONE) {
				checkZFaces(id, x, y, z);
				checkXFaces(id, x, y, z);
				checkYFaces(id, x, y, z);				
			}
		}
		std::string fileName = std::format("Chunk_{}.txt", idx);
		std::stringstream file;
		file << m_vertex.size() << " " << m_index.size() << "\n";
		file << "Vertex\n";
		for (const auto& v : m_vertex) {
			file << v.position.X() << " " << v.position.Y() << " " << v.position.Z() << " " << v.normal.X() << " " << v.normal.Y() << " " << v.normal.Z() << " " << v.uv.X() << " " << v.uv.Y() << "\n";
		}
		file << "Index\n";
		for (const auto& i : m_index) {
			file << i << " ";
			if (i % 128 == 0) file << "\n";
		}
		std::string fileData = file.str();
		{
			std::scoped_lock<std::mutex> lock(MTFunctions::queue_mutex);
			MTFunctions::fileLogQueue.emplace(fileName, fileData);
			MTFunctions::cv.notify_one();
		}
	}

	void Chunk::checkZFaces(UINT& id, int x, int y, int z) {
		if (z > 0 && z <= 127 && m_blocks[x][y][z - 1].type == AIR) {
			m_vertex.append_range(CreateVertexForFace(m_blocks[x][y][z], FRONT));
			m_index.append_range(std::list<UINT>{id, id + 1, id + 2, id, id + 2, id + 3});
			id += 4;
		}
		if (z >= 0 && z < 127 && m_blocks[x][y][z + 1].type == AIR) {
			m_vertex.append_range(CreateVertexForFace(m_blocks[x][y][z], BACK));
			m_index.append_range(std::list<UINT>{id, id + 1, id + 2, id, id + 2, id + 3});
			id += 4;
		}
		if (z == 0 || z == 127) {
			m_vertex.append_range(CreateVertexForFace(m_blocks[x][y][z], z == 0 ? FRONT : BACK));
			m_index.append_range(std::list<UINT>{id, id + 1, id + 2, id, id + 2, id + 3});
			id += 4;
		}
	}

	void Chunk::checkXFaces(UINT& id, int x, int y, int z)
	{
		if (x > 0 && x <= 127 && m_blocks[x - 1][y][z].type == AIR) {
			m_vertex.append_range(CreateVertexForFace(m_blocks[x][y][z], LEFT));
			m_index.append_range(std::list<UINT>{id, id + 1, id + 2, id, id + 2, id + 3});
			id += 4;
		}
		if (x >= 0 && x < 127 && m_blocks[x + 1][y][z].type == AIR) {
			m_vertex.append_range(CreateVertexForFace(m_blocks[x][y][z], RIGHT));
			m_index.append_range(std::list<UINT>{id, id + 1, id + 2, id, id + 2, id + 3});
			id += 4;
		}
		if (x == 0 || x == 127) {
			m_vertex.append_range(CreateVertexForFace(m_blocks[x][y][z], x == 0 ? LEFT : RIGHT));
			m_index.append_range(std::list<UINT>{id, id + 1, id + 2, id, id + 2, id + 3});
			id += 4;
		}
	}

	void Chunk::checkYFaces(UINT& id, int x, int y, int z)
	{
		if (y > 0 && y <= 255 && m_blocks[x][y - 1][z].type == AIR) {
			m_vertex.append_range(CreateVertexForFace(m_blocks[x][y][z], BOTTOM));
			m_index.append_range(std::list<UINT>{id, id + 1, id + 2, id, id + 2, id + 3});
			id += 4;
		}
		if (y >= 0 && z < 255 && m_blocks[x][y + 1][z].type == AIR) {
			m_vertex.append_range(CreateVertexForFace(m_blocks[x][y][z], TOP));
			m_index.append_range(std::list<UINT>{id, id + 1, id + 2, id, id + 2, id + 3});
			id += 4;
		}
		if (y == 0 || y == 256) {
			m_vertex.append_range(CreateVertexForFace(m_blocks[x][y][z], y == 0 ? BOTTOM : TOP));
			m_index.append_range(std::list<UINT>{id, id + 1, id + 2, id, id + 2, id + 3});
			id += 4;
		}
	}

	std::list<vertexData> Chunk::CreateVertexForFace(Block b, Face f) {
		//InstrumentationTimer timer("Create Vertex For Face Scope");
		std::list<vertexData> vertices;
		for (auto i : std::ranges::iota_view{ 0,4 }) {
			auto vertex = LMath::LVector3((float)((b.pos & 0x00FF0000) >> 16) + blockBasicVertices[blockVerticesIndex[f][i]].X(), (float)((b.pos & 0x0000FF00) >> 8) + blockBasicVertices[blockVerticesIndex[f][i]].Y(), (float)((b.pos & 0x000000FF) >> 0) + blockBasicVertices[blockVerticesIndex[f][i]].Z());
			vertices.emplace_back(vertex, blockNormals[f], blockTextCoords[b.type]);
		}
		return vertices;
	}


}