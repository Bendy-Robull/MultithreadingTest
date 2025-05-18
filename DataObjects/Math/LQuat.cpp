#include "../../pch.h"
#include "LQuat.h"
namespace LMath {
	LQuat::LQuat(const LRotator& rot)
	{
		float HalfRoll = 0.5f * (rot.Roll() * DegToRad);
		float HalfPitch = - 0.5f * (rot.Pitch() * DegToRad);
		float HalfYaw = 0.5f * (rot.Yaw() * DegToRad);

		float SinRoll = std::sin(HalfRoll);
		float CosRoll = std::cos(HalfRoll);
		float SinPitch = std::sin(HalfPitch);
		float CosPitch = std::cos(HalfPitch);
		float SinYaw = std::sin(HalfYaw);
		float CosYaw = std::cos(HalfYaw);

		if (std::abs(CosYaw) < KindaSmallNumber) CosYaw = 0.0f;
		if (std::abs(SinYaw) < KindaSmallNumber) SinYaw = 0.0f;
		if (std::abs(CosPitch) < KindaSmallNumber) CosPitch = 0.0f;
		if (std::abs(SinPitch) < KindaSmallNumber) SinPitch = 0.0f;
		if (std::abs(CosRoll) < KindaSmallNumber) CosRoll = 0.0f;
		if (std::abs(SinRoll) < KindaSmallNumber) SinRoll = 0.0f;

		// Create the quaternion from Euler angles
		data[0] = CosRoll * CosPitch * CosYaw + SinRoll * SinPitch * SinYaw;
		data[1] = SinRoll * CosPitch * CosYaw - CosRoll * SinPitch * SinYaw;
		data[2] = CosRoll * SinPitch * CosYaw + SinRoll * CosPitch * SinYaw;
		data[3] = CosRoll * CosPitch * SinYaw - SinRoll * SinPitch * CosYaw;
	}
	LQuat LQuat::GetNormalized()
	{
		float Recip = 1.0f / Size();
		return LQuat(x * Recip, y * Recip, z * Recip, w * Recip);
	}

	LQuat LQuat::Inverse()
	{
		float Recip = 1.0f / (x * x + y * y + z * z + w * w);
		return LQuat(-x * Recip, -y * Recip, -z * Recip, w * Recip);
	}

	LRotator LQuat::RotatorLH()
	{
		// roll (z-axis rotation)
		float sinr_cosp = 2 * (w * x + y * z);
		float cosr_cosp = 1 - 2 * (x * x + y * y);
		float roll = std::atan2(sinr_cosp, cosr_cosp);

		// pitch (y-axis rotation)
		float sinp = 2 * (w * y - z * x);
		float pitch = 0.f;
		if (std::abs(sinp) >= 1)
			pitch = std::copysign(std::numbers::pi_v<float> / 2, sinp); // use 90 degrees if out of range
		else
			pitch = std::asin(sinp);

		// yaw (x-axis rotation)
		float siny_cosp = 2 * (w * z + x * y);
		float cosy_cosp = 1 - 2 * (y * y + z * z);
		float yaw = std::atan2(siny_cosp, cosy_cosp);
		return LRotator(yaw * RadToDeg, -pitch * RadToDeg, roll * RadToDeg);
	}

	LMatrix LQuat::Matrix()
	{
		float xx = x * x;
		float xy = x * y;
		float xz = x * z;
		float yy = y * y;
		float yz = y * z;
		float zz = z * z;
		float wx = w * x;
		float wy = w * y;
		float wz = w * z;

		return LMatrix(
			1.0f - 2 * yy - 2 * zz, 2 * xy - 2 * wz, 2 * xz + 2 * wy, 0.0f,
			2 * xy + 2 * wz, 1.0f - 2 * xx - 2 * zz, 2 * yz - 2 * wx, 0.0f,
			2 * xz - 2 * wy, 2 * yz + 2 * wx, 1.0f - 2 * xx - 2 * yy, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	STRING LQuat::ToString()
	{
		std::ostringstream oss;
		oss << "LQuat(" << w << ", " << x << ", " << y << ", " << z << ")";
		return STRING(oss.str().c_str());
	}

	static const LQuat Identity = LQuat(0.0f, 0.0f, 0.0f, 1.0f);
}