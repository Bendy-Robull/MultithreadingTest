#pragma once
#include <array>
#include <numbers>
#include <numeric>
#include <cmath>
#include <algorithm>

#define Pi 3.1415926535897932f
#define DegToRad Pi / 180.0f
#define RadToDeg 180.0f / Pi
#define KindaSmallNumber 0.0001f

#define check(x) assert(x);

namespace LMath {
	enum EAxis { X, Y, Z };
	struct LVector3; // Forward declaration
	struct LVector4; // Forward declaration
	struct LRotator; // Forward declaration
	struct LQuat;    // Forward declaration
	struct LMatrix;  // Forward declaration
}

//#include "Core/Math/LVector.h"
//#include "Core/Math/LRotator.h"
//#include "Core/Math/LQuat.h"
//#include "Core/Math/LMatrix.h"