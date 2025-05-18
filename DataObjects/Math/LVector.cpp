#include "../../pch.h"


namespace LMath{
    LVector3::LVector3(const LVector4& vec4) : vectorData{ vec4.X(), vec4.Y(), vec4.Z() } {}
    LRotator LVector3::Rotation() const
    {
        // Normalize the vector first.
        LVector3 V = *this;
        V.Normalize();

        // Calculate Pitch
        float Pitch = atan2(-V.Y(), sqrt(V.X() * V.X() + V.Z() * V.Z()));

        // Calculate Yaw
		float Yaw = 0.f;
        if (V.X() != 0.0f || V.Z() != 0.0f)
        {
           Yaw = atan2(V.X(), V.Z());
        }
        return LRotator(Yaw * RadToDeg, Pitch * RadToDeg, 0.0f);
    }

    const LVector3 LVector3::ZeroVector = LVector3();
    const LVector3 LVector3::UnitVector = LVector3(1);
    const LVector3 LVector3::UpVector = LVector3(0, 1, 0);
    const LVector3 LVector3::RightVector = LVector3(1, 0, 0);
    const LVector3 LVector3::ForwardVector = LVector3(0, 0, 1);

    const LVector4 LVector4::ZeroVector = LVector4();
    const LVector4 LVector4::UnitVector = LVector4(1);
    const LVector4 LVector4::UpVector = LVector4(0, 1, 0);
    const LVector4 LVector4::RightVector = LVector4(1, 0, 0);
    const LVector4 LVector4::ForwardVector = LVector4(0, 0, 1);
}