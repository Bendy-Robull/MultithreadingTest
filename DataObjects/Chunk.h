#pragma once
namespace Project::Components{


	class Chunk
	{
	public:
		enum BlockType {
			AIR = 1000,
			STONE = 0
		};
		enum Face {
			FRONT = 0,
			BACK = 1,
			LEFT = 2,
			RIGHT = 3,
			BOTTOM = 4,
			TOP = 5
		};
		struct Block {
			BlockType type;
			int pos = 0;
			Block() {
				type = AIR;
			}
		};
		std::vector<LMath::LVector2> blockTextCoords{
		LMath::LVector2( 0.546875, 0.5f)
		};
		std::array<LMath::LVector3,8> blockBasicVertices{
			LMath::LVector3( -0.5f,  -0.5f,  -0.5f),
			LMath::LVector3( -0.5f,  +0.5f,  -0.5f),
			LMath::LVector3( +0.5f,  +0.5f,  -0.5f),
			LMath::LVector3( +0.5f,  -0.5f,  -0.5f),
			LMath::LVector3( +0.5f,  -0.5f,  +0.5f),
			LMath::LVector3( +0.5f,  +0.5f,  +0.5f),
			LMath::LVector3( -0.5f,  +0.5f,  +0.5f),
			LMath::LVector3( -0.5f,  -0.5f,  +0.5f),
		};
		int blockVerticesIndex[6][4]{
			//front vertices
			{
				0,
				1,
				2,
				3
			},
			//back vertices
			{
				4,
				5,
				6,
				7,
			},
			//left vertices
			{
				7,
				6,
				1,
				0
			},
			//right vertices
			{
				3,
				2,
				5,
				4
			},
			//bottom vertices
			{
				7,
				0,
				3,
				4
			},
			//top vertices
			{
				1,
				6,
				5,
				2
			}
		};
		std::vector<LMath::LVector3> blockNormals = {
		LMath::LVector3(0.f, 0.f, -1.f),
		LMath::LVector3(0.f, 0.f, +1.f),
		LMath::LVector3(-1.f, 0.f, 0.f),
		LMath::LVector3(+1.f, 0.f, 0.f),
		LMath::LVector3(0.f, -1.f, 0.f),
		LMath::LVector3(0.f, +1.f, 0.f),
		};

		Chunk() = default;
		Chunk(int idx, const LMath::LVector3& pos,std::shared_ptr<Engine::PerlinNoiseGenerator> perlinGenerator);
		void CreateMesh(int idx);
		void checkZFaces(UINT& id, int x, int y, int z);
		void checkXFaces(UINT& id, int x, int y, int z);
		void checkYFaces(UINT& id, int x, int y, int z);

		std::list<vertexData> CreateVertexForFace(Block b, Face f);

	private:
		std::vector<std::vector<std::vector<Block>>> m_blocks;
		std::vector<vertexData> m_vertex;
		std::vector<UINT> m_index;

	};
}
