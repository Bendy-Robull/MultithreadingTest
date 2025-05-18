#pragma once
#include "LMath.h"
#include "LVector.h"
#include "LRotator.h"
#include "LQuat.h"
namespace LMath {

		struct LMatrix
	{
	public:
		LMatrix(
			float InM00, float InM01, float InM02, float InM03,
			float InM10, float InM11, float InM12, float InM13,
			float InM20, float InM21, float InM22, float InM23,
			float InM30, float InM31, float InM32, float InM33
		);
	private:
		std::array<std::array<float, 4>, 4> m_Data;
	public:
		// Operators.

		LMatrix operator+(const LMatrix& Other) const {
			LMatrix Result = *this;
			Result.m_Data[0][0] = m_Data[0][0] + Other.m_Data[0][0];
			Result.m_Data[0][1] = m_Data[0][1] + Other.m_Data[0][1];
			Result.m_Data[0][2] = m_Data[0][2] + Other.m_Data[0][2];
			Result.m_Data[0][3] = m_Data[0][3] + Other.m_Data[0][3];
			Result.m_Data[1][0] = m_Data[1][0] + Other.m_Data[1][0];
			Result.m_Data[1][1] = m_Data[1][1] + Other.m_Data[1][1];
			Result.m_Data[1][2] = m_Data[1][2] + Other.m_Data[1][2];
			Result.m_Data[1][3] = m_Data[1][3] + Other.m_Data[1][3];
			Result.m_Data[2][0] = m_Data[2][0] + Other.m_Data[2][0];
			Result.m_Data[2][1] = m_Data[2][1] + Other.m_Data[2][1];
			Result.m_Data[2][2] = m_Data[2][2] + Other.m_Data[2][2];
			Result.m_Data[2][3] = m_Data[2][3] + Other.m_Data[2][3];
			Result.m_Data[3][0] = m_Data[3][0] + Other.m_Data[3][0];
			Result.m_Data[3][1] = m_Data[3][1] + Other.m_Data[3][1];
			Result.m_Data[3][2] = m_Data[3][2] + Other.m_Data[3][2];
			Result.m_Data[3][3] = m_Data[3][3] + Other.m_Data[3][3];
			return Result;
		}
		LMatrix operator-(const LMatrix& Other) const {
			LMatrix Result = *this;
			Result.m_Data[0][0] = m_Data[0][0] - Other.m_Data[0][0];
			Result.m_Data[0][1] = m_Data[0][1] - Other.m_Data[0][1];
			Result.m_Data[0][2] = m_Data[0][2] - Other.m_Data[0][2];
			Result.m_Data[0][3] = m_Data[0][3] - Other.m_Data[0][3];
			Result.m_Data[1][0] = m_Data[1][0] - Other.m_Data[1][0];
			Result.m_Data[1][1] = m_Data[1][1] - Other.m_Data[1][1];
			Result.m_Data[1][2] = m_Data[1][2] - Other.m_Data[1][2];
			Result.m_Data[1][3] = m_Data[1][3] - Other.m_Data[1][3];
			Result.m_Data[2][0] = m_Data[2][0] - Other.m_Data[2][0];
			Result.m_Data[2][1] = m_Data[2][1] - Other.m_Data[2][1];
			Result.m_Data[2][2] = m_Data[2][2] - Other.m_Data[2][2];
			Result.m_Data[2][3] = m_Data[2][3] - Other.m_Data[2][3];
			Result.m_Data[3][0] = m_Data[3][0] - Other.m_Data[3][0];
			Result.m_Data[3][1] = m_Data[3][1] - Other.m_Data[3][1];
			Result.m_Data[3][2] = m_Data[3][2] - Other.m_Data[3][2];
			Result.m_Data[3][3] = m_Data[3][3] - Other.m_Data[3][3];
			return Result;
		}
		LMatrix operator*(const LMatrix& Other) const; // Matrix multiplication
		LVector4 operator*(const LVector4& V) const; // Matrix-vector multiplication
		LMatrix operator*(float Scale) const{
			LMatrix Result = *this;
			Result.m_Data[0][0] = m_Data[0][0] * Scale;
			Result.m_Data[0][1] = m_Data[0][1] * Scale;
			Result.m_Data[0][2] = m_Data[0][2] * Scale;
			Result.m_Data[0][3] = m_Data[0][3] * Scale;
			Result.m_Data[1][0] = m_Data[1][0] * Scale;
			Result.m_Data[1][1] = m_Data[1][1] * Scale;
			Result.m_Data[1][2] = m_Data[1][2] * Scale;
			Result.m_Data[1][3] = m_Data[1][3] * Scale;
			Result.m_Data[2][0] = m_Data[2][0] * Scale;
			Result.m_Data[2][1] = m_Data[2][1] * Scale;
			Result.m_Data[2][2] = m_Data[2][2] * Scale;
			Result.m_Data[2][3] = m_Data[2][3] * Scale;
			Result.m_Data[3][0] = m_Data[3][0] * Scale;
			Result.m_Data[3][1] = m_Data[3][1] * Scale;
			Result.m_Data[3][2] = m_Data[3][2] * Scale;
			Result.m_Data[3][3] = m_Data[3][3] * Scale;
			return Result;
		}  // Matrix scalar multiplication
		
		bool operator==(const LMatrix& Other) const {
			return m_Data == Other.m_Data;
		}
		bool operator!=(const LMatrix& Other) const {
			return m_Data != Other.m_Data;
		}

		// Functions.
		//LMatrix GetTransposed() const;
		//LMatrix GetInverted() const;
		//LMatrix GetInvertedNotConsiderScale() const;
		//LVector3 GetOrigin() const;
		LVector3 GetAxis(EAxis InAxis) const; // Collumn
		//LVector3 GetScaleVector() const;
		//LQuat Quaternion() const;
		//LRotator Rotator() const;
		STRING ToString() const;

		static LMatrix RotationMatrixLH(const LRotator& rot);
		static LMatrix RotationMatrix(const LQuat& quat);

		// Constants.
		static const LMatrix Identity;
		
	};

}