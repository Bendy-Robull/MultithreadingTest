#include "../../pch.h"
#include "LMatrix.h"
namespace LMath {
    LMatrix::LMatrix(float InM00, float InM01, float InM02, float InM03, float InM10, float InM11, float InM12, float InM13, float InM20, float InM21, float InM22, float InM23, float InM30, float InM31, float InM32, float InM33)
    {
    m_Data[0][0] = abs(InM00) < KindaSmallNumber ?  0.f : InM00; 
    m_Data[0][1] = abs(InM01) < KindaSmallNumber ?  0.f : InM01; 
    m_Data[0][2] = abs(InM02) < KindaSmallNumber ?  0.f : InM02; 
    m_Data[0][3] = abs(InM03) < KindaSmallNumber ?  0.f : InM03;
    m_Data[1][0] = abs(InM10) < KindaSmallNumber ?  0.f : InM10; 
    m_Data[1][1] = abs(InM11) < KindaSmallNumber ?  0.f : InM11; 
    m_Data[1][2] = abs(InM12) < KindaSmallNumber ?  0.f : InM12; 
    m_Data[1][3] = abs(InM13) < KindaSmallNumber ?  0.f : InM13;
    m_Data[2][0] = abs(InM20) < KindaSmallNumber ?  0.f : InM20; 
    m_Data[2][1] = abs(InM21) < KindaSmallNumber ?  0.f : InM21; 
    m_Data[2][2] = abs(InM22) < KindaSmallNumber ?  0.f : InM22; 
    m_Data[2][3] = abs(InM23) < KindaSmallNumber ?  0.f : InM23;
    m_Data[3][0] = abs(InM30) < KindaSmallNumber ?  0.f : InM30; 
    m_Data[3][1] = abs(InM31) < KindaSmallNumber ?  0.f : InM31; 
    m_Data[3][2] = abs(InM32) < KindaSmallNumber ?  0.f : InM32; 
    m_Data[3][3] = abs(InM33) < KindaSmallNumber ?  0.f : InM33;
    }	


    LMatrix LMatrix::operator*(const LMatrix& Other) const
    {
		LMatrix Result(
			Other.m_Data[0][0] * m_Data[0][0] + Other.m_Data[0][1] * m_Data[1][0] + Other.m_Data[0][2] * m_Data[2][0] + Other.m_Data[0][3] * m_Data[3][0],
			Other.m_Data[0][0] * m_Data[0][1] + Other.m_Data[0][1] * m_Data[1][1] + Other.m_Data[0][2] * m_Data[2][1] + Other.m_Data[0][3] * m_Data[3][1],
			Other.m_Data[0][0] * m_Data[0][2] + Other.m_Data[0][1] * m_Data[1][2] + Other.m_Data[0][2] * m_Data[2][2] + Other.m_Data[0][3] * m_Data[3][2],
			Other.m_Data[0][0] * m_Data[0][3] + Other.m_Data[0][1] * m_Data[1][3] + Other.m_Data[0][2] * m_Data[2][3] + Other.m_Data[0][3] * m_Data[3][3],
			Other.m_Data[1][0] * m_Data[0][0] + Other.m_Data[1][1] * m_Data[1][0] + Other.m_Data[1][2] * m_Data[2][0] + Other.m_Data[1][3] * m_Data[3][0],
			Other.m_Data[1][0] * m_Data[0][1] + Other.m_Data[1][1] * m_Data[1][1] + Other.m_Data[1][2] * m_Data[2][1] + Other.m_Data[1][3] * m_Data[3][1],
			Other.m_Data[1][0] * m_Data[0][2] + Other.m_Data[1][1] * m_Data[1][2] + Other.m_Data[1][2] * m_Data[2][2] + Other.m_Data[1][3] * m_Data[3][2],
			Other.m_Data[1][0] * m_Data[0][3] + Other.m_Data[1][1] * m_Data[1][3] + Other.m_Data[1][2] * m_Data[2][3] + Other.m_Data[1][3] * m_Data[3][3],
			Other.m_Data[2][0] * m_Data[0][0] + Other.m_Data[2][1] * m_Data[1][0] + Other.m_Data[2][2] * m_Data[2][0] + Other.m_Data[2][3] * m_Data[3][0],
			Other.m_Data[2][0] * m_Data[0][1] + Other.m_Data[2][1] * m_Data[1][1] + Other.m_Data[2][2] * m_Data[2][1] + Other.m_Data[2][3] * m_Data[3][1],
			Other.m_Data[2][0] * m_Data[0][2] + Other.m_Data[2][1] * m_Data[1][2] + Other.m_Data[2][2] * m_Data[2][2] + Other.m_Data[2][3] * m_Data[3][2],
			Other.m_Data[2][0] * m_Data[0][3] + Other.m_Data[2][1] * m_Data[1][3] + Other.m_Data[2][2] * m_Data[2][3] + Other.m_Data[2][3] * m_Data[3][3],
			Other.m_Data[3][0] * m_Data[0][0] + Other.m_Data[3][1] * m_Data[1][0] + Other.m_Data[3][2] * m_Data[2][0] + Other.m_Data[3][3] * m_Data[3][0],
			Other.m_Data[3][0] * m_Data[0][1] + Other.m_Data[3][1] * m_Data[1][1] + Other.m_Data[3][2] * m_Data[2][1] + Other.m_Data[3][3] * m_Data[3][1],
			Other.m_Data[3][0] * m_Data[0][2] + Other.m_Data[3][1] * m_Data[1][2] + Other.m_Data[3][2] * m_Data[2][2] + Other.m_Data[3][3] * m_Data[3][2],
			Other.m_Data[3][0] * m_Data[0][3] + Other.m_Data[3][1] * m_Data[1][3] + Other.m_Data[3][2] * m_Data[2][3] + Other.m_Data[3][3] * m_Data[3][3]
		);
		return Result;
    }

	LVector4 LMatrix::operator*(const LVector4& V) const
	{
		return LVector4(
			m_Data[0][0] * V.X() + m_Data[0][1] * V.Y() + m_Data[0][2] * V.Z() + m_Data[0][3] * V.W(),
			m_Data[1][0] * V.X() + m_Data[1][1] * V.Y() + m_Data[1][2] * V.Z() + m_Data[1][3] * V.W(),
			m_Data[2][0] * V.X() + m_Data[2][1] * V.Y() + m_Data[2][2] * V.Z() + m_Data[2][3] * V.W(),
			m_Data[3][0] * V.X() + m_Data[3][1] * V.Y() + m_Data[3][2] * V.Z() + m_Data[3][3] * V.W()
		);
	}

	LVector3 LMatrix::GetAxis(EAxis InAxis) const
	{
		switch (InAxis)
		{
		case EAxis::X:
			return LVector3(m_Data[0][0], m_Data[1][0], m_Data[2][0]);
		case EAxis::Y:
			return LVector3(m_Data[0][1], m_Data[1][1], m_Data[2][1]);
		case EAxis::Z:
			return LVector3(m_Data[0][2], m_Data[1][2], m_Data[2][2]);
		default:
			check(0); // Invalid axis
			return LVector3::ZeroVector;
		}
	}

    STRING LMatrix::ToString() const
    {
        std::ostringstream oss;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                oss << m_Data[i][j];
                if (j < 3) oss << ", ";
            }
            if (i < 3) oss << "; ";
        }
        return STRING(oss.str().c_str());
    }

	static const LMatrix Identity = LMatrix(
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	);

	LMatrix LMatrix::RotationMatrixLH(const LRotator& rot)
	{
		float yawRad = rot.Yaw() * DegToRad;
		float pitchRad = rot.Pitch() * DegToRad;
		float rollRad = rot.Roll() * DegToRad;

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

	LMatrix LMatrix::RotationMatrix(const LQuat& quat)
	{
		float xx = quat.X() * quat.X();
		float xy = quat.X() * quat.Y();
		float xz = quat.X() * quat.Z();
		float yy = quat.Y() * quat.Y();
		float yz = quat.Y() * quat.Z();
		float zz = quat.Z() * quat.Z();
		float wx = quat.W() * quat.X();
		float wy = quat.W() * quat.Y();
		float wz = quat.W() * quat.Z();

		return LMatrix(
			1.0f - 2 * yy - 2 * zz, 2 * xy - 2 * wz, 2 * xz + 2 * wy, 0.0f,
			2 * xy + 2 * wz, 1.0f - 2 * xx - 2 * zz, 2 * yz - 2 * wx, 0.0f,
			2 * xz - 2 * wy, 2 * yz + 2 * wx, 1.0f - 2 * xx - 2 * yy, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

}