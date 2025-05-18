#pragma once
#include "LMath.h"
#include "LVector.h"
#include "LRotator.h"
#include "LMatrix.h"
namespace LMath {
	struct LQuat // Always Right-Handed
	{
	public:		
		LQuat(float w, float x, float y, float z) : data{ w,x,y,z } {}
		LQuat(const LQuat& other) : data(other.data) {}
		LQuat(const LRotator& rot);
	private:
		float& w = data[0];
		float& x = data[1];
		float& y = data[2];
		float& z = data[3];
		std::array<float, 4> data = { 0,0,0,0 };
	public:
		//float& operator[](std::uint32_t Index) { check(Index >= 0 && Index < 4); return (&x)[Index]; }
		//const float& operator[](std::uint32_t Index) const { check(Index >= 0 && Index < 4); return (&x)[Index]; }

		// Operators.
		LQuat operator+(const LQuat& Q) { return LQuat(x + Q.x, y + Q.y, z + Q.z, w + Q.w); }
		LQuat operator-(const LQuat& Q) { return LQuat(x - Q.x, y - Q.y, z - Q.z, w - Q.w); }
		LQuat operator*(const LQuat& Q) { 
			return LQuat(
				w * Q.w - x * Q.x - y * Q.y - z * Q.z,
				w * Q.x + x * Q.w + y * Q.z - z * Q.y,
				w * Q.y + y * Q.w + z * Q.x - x * Q.z,
				w * Q.z + z * Q.w + x * Q.y - y * Q.x
			);
		}
		LQuat operator*(float Scale)  { return LQuat(x * Scale, y * Scale, z * Scale, w * Scale); }
		friend LQuat operator*(float Scale, const LQuat& Q) { return LQuat(Q.x * Scale, Q.y * Scale, Q.z * Scale, Q.w * Scale); }
		LQuat operator/(float Scale)  { return LQuat(x / Scale, y / Scale, z / Scale, w / Scale); }
		LQuat operator-()  { return LQuat(-x, -y, -z, -w); }
		bool operator==(const LQuat& Q) const { return std::abs(x - Q.x) <= KindaSmallNumber && std::abs(y - Q.y) <= KindaSmallNumber && std::abs(z - Q.z) <= KindaSmallNumber && std::abs(w - Q.w) <= KindaSmallNumber; }
		bool operator!=(const LQuat& Q) const { return !(*this == Q); }

		// Functions.
		float Size() const { return std::sqrt(x * x + y * y + z * z + w * w); }
		float SizeSquared() const { return x * x + y * y + z * z + w * w; }
		LQuat GetNormalized();
		LQuat Inverse();
		LRotator RotatorLH();
		LMatrix Matrix(); //Also always RH
		STRING ToString();

	public: // Getters
		float W() const { return w; }
		float X() const { return x; }
		float Y() const { return y; }
		float Z() const { return z; }

	public: // Constants.
		static const LQuat Identity;	
	};

}