#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <execution>
#include <thread>
#include <assert.h>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <functional>
#include <ranges>
#include <algorithm>
#include <math.h>
#include <latch>
#include <barrier>
#include <chrono>
#include <format>
#define STRING std::string
using UINT = unsigned int;

#include "Instrumentor.h"
#include "DataObjects/Math/LMath.h"
#include "DataObjects/Math/LRotator.h"
#include "DataObjects/Math/LVector.h"
#include "DataObjects/Math/LQuat.h"
#include "DataObjects/Math/LMatrix.h"



struct  vertexData {
	LMath::LVector3 position;
	LMath::LVector3 normal;
	LMath::LVector2 uv;

	vertexData(const LMath::LVector3& position, const LMath::LVector3& normal, const LMath::LVector2& uv) :
		position(position),
		normal(normal),
		uv(uv)
	{}
	vertexData() = default;
};

#include "DataObjects/PerlinNoiseGenerator.h"
#include "DataObjects/Chunk.h"
#include "MTFunctions.h"
#include "Multithreading/FunctionThread.h"
#include "Multithreading/ConsoleThread.h"

