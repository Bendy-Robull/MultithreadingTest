#pragma once

namespace LMath {

	struct LVector3
	{
	public:

		LVector3() = default;
		LVector3(float x, float y, float z) : vectorData{ x, y, z } {}
		explicit LVector3(float scalar) : vectorData{ scalar, scalar, scalar } {}
		LVector3(const LVector3& vec3) : vectorData{ vec3.x,vec3.y,vec3.z } {}
		explicit LVector3(const LVector4& vec4);
	private:
		std::array<float, 3> vectorData = { 0.f, 0.f, 0.f };
	private:
		float& x = vectorData[0];
		float& y = vectorData[1];
		float& z = vectorData[2];
	public:
		LVector3& operator=(const LVector3& vec) {
			if (this != &vec) {
				vectorData[0] = vec.vectorData[0];
				vectorData[1] = vec.vectorData[1];
				vectorData[2] = vec.vectorData[2];
			}
			return *this;
		}
		friend LVector3 operator+(const LVector3& lhs, const LVector3& rhs) { return LVector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }
		friend LVector3 operator-(const LVector3& lhs, const LVector3& rhs) { return LVector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }
		friend LVector3 operator*(const LVector3& vec, const float& scalar) { return LVector3(vec.x * scalar, vec.y * scalar, vec.z * scalar); }
		friend LVector3 operator/(const LVector3& vec, const float& scalar) { return LVector3(vec.x / scalar, vec.y / scalar, vec.z / scalar); }
		bool operator==(const LVector3& vec) const { return vectorData[0] == vec.x && vectorData[1] == vec.y && vectorData[2] == vec.z; }


		float DotProduct(const LVector3& vec) const { return std::inner_product(vectorData.begin(), vectorData.end(), vec.vectorData.begin(), 0.f); }
		LVector3 CrossProduct(const LVector3& vec) const { return LVector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x); }
		float Length() const noexcept { return sqrt(vectorData[0] * vectorData[0] + vectorData[1] * vectorData[1] + vectorData[2] * vectorData[2]); }
		float LengthSquared() const noexcept { return vectorData[0] * vectorData[0] + vectorData[1] * vectorData[1] + vectorData[2] * vectorData[2]; }
		LVector3 Normal() noexcept
		{
			if (float length = Length(); (length - 1.f) > KindaSmallNumber) {
				return LVector3(vectorData[0] / length, vectorData[1] / length, vectorData[2] / length);
			}
			return LVector3(*this);
		}

		void Normalize() noexcept
		{
			float length = Length();
			if (length - 1.f > KindaSmallNumber) {
				vectorData[0] /= length;
				vectorData[1] /= length;
				vectorData[2] /= length;
			}
		}
		LVector3 GetSafeNormal() { return (vectorData == LVector3::ZeroVector.vectorData) ? LVector3::ZeroVector : Normal(); }
		float Distance(const LVector3& vec) const { return sqrt((x - vec.x) * (x - vec.x) + (y - vec.y) * (y - vec.y) + (z - vec.z) * (z - vec.z)); }
		float DistanceSquared(const LVector3& vec) const { return (x - vec.x) * (x - vec.x) + (y - vec.y) * (y - vec.y) + (z - vec.z) * (z - vec.z); }
		LVector3 ProjectOnTo(LVector3 vec) const { return LVector3(DotProduct(vec.Normal())); }
		LRotator Rotation() const;
		bool IsNearZero() const noexcept { return LengthSquared() < 0.01f; }

	public: // Getters
		float& X() const { return x; }
		float& Y() const { return y; }
		float& Z() const { return z; }
	public:
		static const LVector3 UnitVector;
		static const LVector3 ZeroVector;
		static const LVector3 UpVector;
		static const LVector3 RightVector;
		static const LVector3 ForwardVector;

	};

	struct LVector4
	{
	public:
		LVector4() = default;
		LVector4(float x, float y, float z, bool point = false) : vectorData{ x, y, z, point ? 1.f : 0.f } {}
		LVector4(float x, float y, float z, float w) : vectorData{ x, y, z, w } {}
		LVector4(float scalar, bool point = false) : vectorData{ scalar, scalar, scalar, point ? 1.f : 0.f } {}
		LVector4(const LVector3& vec3, bool point = false) : vectorData{ vec3.X(), vec3.Y(), vec3.Z() ,point ? 1.f : 0.f } {}
	private:
		std::array<float, 4> vectorData = { 0.f, 0.f, 0.f ,0.f };
	private:
		float& x = vectorData[0];
		float& y = vectorData[1];
		float& z = vectorData[2];
		float& w = vectorData[3];
	public:
		friend LVector4 operator+(const LVector4& lhs, const LVector4& rhs) { return LVector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
		friend LVector4 operator-(const LVector4& lhs, const LVector4& rhs) { return LVector4(lhs.vectorData[0] - rhs.x, lhs.vectorData[1] - rhs.y, lhs.vectorData[2] - rhs.z, lhs.vectorData[3] - rhs.w); }
		friend LVector4 operator*(const LVector4& vec, const float& scalar) { return LVector4(vec.vectorData[0] * scalar, vec.vectorData[1] * scalar, vec.vectorData[2] * scalar, vec.vectorData[3] * scalar); }
		friend LVector4 operator/(const LVector4& vec, const float& scalar) { return LVector4(vec.vectorData[0] / scalar, vec.vectorData[1] / scalar, vec.vectorData[2] / scalar, vec.vectorData[3] / scalar); }
		
		LVector4& operator=(const LVector4& vec) {
			if (this != &vec) {
				vectorData[0] = vec.x;
				vectorData[1] = vec.y;
				vectorData[2] = vec.z;
				vectorData[3] = vec.w;
			}
			return *this;
		}
		bool operator==(const LVector4& vec) const { return vectorData[0] == vec.x && vectorData[1] == vec.y && vectorData[2] == vec.z && vectorData[3] == vec.w; }
		LVector3 ToVector3() { return LVector3(vectorData[0], vectorData[1], vectorData[2]); }

	public:
		float& X() const { return x; }
		float& Y() const { return y; }
		float& Z() const { return z; }
		float& W() const { return w; }
	public:
		static const LVector4 UnitVector;
		static const LVector4 ZeroVector;
		static const LVector4 UpVector;
		static const LVector4 RightVector;
		static const LVector4 ForwardVector;

	};


	struct LVector2
	{
	public:
		LVector2() = default;
		LVector2(float x, float y) : vectorData{ x, y } {}
		explicit LVector2(float scalar) : vectorData{ scalar, scalar } {}
		LVector2(const LVector2& vec2) : vectorData{ vec2.x,vec2.y } {}
		LVector2& operator=(const LVector2& vec) {
			vectorData[0] = vec.x;
			vectorData[1] = vec.y;
			return *this;
		}
		float X() const { return x; }
		float Y() const { return y; }
	private:
		std::array<float, 2> vectorData = { 0.f, 0.f };
	private:
		float& x = vectorData[0];
		float& y = vectorData[1];

	};
}
