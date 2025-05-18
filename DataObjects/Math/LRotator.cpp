#include "../../pch.h"

namespace LMath {
	LQuat LRotator::Quaternion() const
	{
		float HalfRoll = 0.5f * m_Roll * DegToRad;
		float HalfPitch = -0.5f * m_Pitch * DegToRad;
		float HalfYaw = 0.5f * m_Yaw * DegToRad;
		// Calculate the half-angles

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
		float W = CosRoll * CosPitch * CosYaw + SinRoll * SinPitch * SinYaw;
		float X = SinRoll * CosPitch * CosYaw - CosRoll * SinPitch * SinYaw;
		float Y = CosRoll * SinPitch * CosYaw + SinRoll * CosPitch * SinYaw;
		float Z = CosRoll * CosPitch * SinYaw - SinRoll * SinPitch * CosYaw;
		return LQuat(W, X, Y, Z);
	}	
	LVector3 LRotator::Vector() const
	{
		return (MatrixLH() * LVector4::ForwardVector).ToVector3();
	}
	LMatrix LRotator::MatrixLH() const
	{
		// Convert angles to radians
		float yawRad = m_Yaw * DegToRad;
		float pitchRad = m_Pitch * DegToRad;
		float rollRad = m_Roll * DegToRad;

		// Create rotation matrices
		float cosYaw = std::cos(yawRad);
		float sinYaw = std::sin(yawRad);
		float cosPitch = std::cos(pitchRad);
		float sinPitch = std::sin(pitchRad);
		float cosRoll = std::cos(rollRad);
		float sinRoll = std::sin(rollRad);

		if (std::abs(cosYaw) < KindaSmallNumber) cosYaw = 0.0f;
		if (std::abs(sinYaw) < KindaSmallNumber) sinYaw = 0.0f;
		if (std::abs(cosPitch) < KindaSmallNumber) cosPitch = 0.0f;
		if (std::abs(sinPitch) < KindaSmallNumber) sinPitch = 0.0f;
		if (std::abs(cosRoll) < KindaSmallNumber) cosRoll = 0.0f;
		if (std::abs(sinRoll) < KindaSmallNumber) sinRoll = 0.0f;

		LMatrix yawMatrix(
			cosYaw, 0.0f, sinYaw, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-sinYaw, 0.0f, cosYaw, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		LMatrix pitchMatrix(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cosPitch, -sinPitch, 0.0f,
			0.0f, sinPitch, cosPitch, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		LMatrix rollMatrix(
			cosRoll, -sinRoll, 0.0f, 0.0f,
			sinRoll, cosRoll, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		// Combine the rotation matrices: Roll * Pitch * Yaw
		return rollMatrix * pitchMatrix * yawMatrix;
	}
	LVector3 LRotator::RotateVector(const LVector3& vector) const
	{
		return (MatrixLH() * LVector4(vector)).ToVector3();
	}
	void LRotator::clamp(float yawLimit, float pitchLimit)
	{
		m_Yaw = std::clamp(m_Yaw, -yawLimit,yawLimit);
		m_Pitch = std::clamp(m_Pitch, -pitchLimit, pitchLimit);
	}
}