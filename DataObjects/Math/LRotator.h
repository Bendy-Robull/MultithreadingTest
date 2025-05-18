#pragma once

#include "LMatrix.h"
#include "LVector.h"
#include "LQuat.h"
namespace LMath {

	struct LRotator
	{
	public:
		LRotator(float _yaw, float _pitch, float _roll) : m_Pitch(_pitch), m_Yaw(_yaw), m_Roll(_roll) {}
		LRotator(const LRotator& other) : m_Pitch(other.m_Pitch), m_Yaw(other.m_Yaw), m_Roll(other.m_Roll) {}

		LRotator operator+ (const LRotator& other) const { return LRotator(m_Yaw + other.m_Yaw, m_Pitch + other.m_Pitch, m_Roll + other.m_Roll); }
		LRotator operator- (const LRotator& other) const { return LRotator(m_Yaw - other.m_Yaw, m_Pitch - other.m_Pitch, m_Roll - other.m_Roll); }
		LRotator operator+= (const LRotator& other) {
			m_Yaw += other.m_Yaw;
			m_Pitch += other.m_Pitch;
			m_Roll += other.m_Roll;
			return *this;
		}
		LRotator operator-= (const LRotator& other) {
			m_Yaw -= other.m_Yaw;
			m_Pitch -= other.m_Pitch;
			m_Roll -= other.m_Roll;
			return *this;
		}

        friend std::ostream& operator<<(std::ostream& os, const LRotator& rotator) {
            os << rotator.ToString();
            return os;
        }
		friend std::istream& operator>>(std::istream& is, LRotator& rotator) {
			is >> rotator.m_Yaw >> rotator.m_Pitch >> rotator.m_Roll;
			return is;
		}
	private:
		float m_Pitch = 0.f;
		float m_Yaw = 0.f;
		float m_Roll = 0.f;
	public:
		LRotator GetNormalized() const { return LRotator(std::fmod(m_Yaw, 360.f), std::fmod(m_Pitch, 360.f), std::fmod(m_Roll, 360.f)); }
		LMatrix MatrixLH() const;
		LVector3 RotateVector(const LVector3& vector) const;
		LQuat Quaternion() const;
		bool Equals(const LRotator& other) const { return m_Yaw == other.m_Yaw && m_Pitch == other.m_Pitch && m_Roll == other.m_Roll; }
		LVector3 Vector() const; //returns the forward vector of the Rotator
		void clamp(float yawLimit, float pitchLimit);
		STRING ToString() const {
			return "LRotator(Pitch=" + std::to_string(m_Pitch) + ", Yaw=" + std::to_string(m_Yaw) + ", Roll=" + std::to_string(m_Roll) + ")";
		}

	public: // Getters
		float Yaw() const { return m_Yaw; }
		float Pitch() const { return m_Pitch; }
		float Roll() const { return m_Roll; }
	
		//Distance,Clamp

	};
}