#pragma once

#include"Vec3.h"

class Vec4
{
public:
	Vec4(float x = 0.f, float y = 0.f, float z = 0.f, float w = 1.f);
	Vec4(const Vec3& vec3, float w = 1.0f);

	float m_x;
	float m_y;
	float m_z;
	float m_w;

	void Homogenize();
	float GetMagnitude() const;
	void Normalize();

	Vec4 operator+(Vec4 vector);
	Vec4 operator*(float value);
	Vec4 operator-(Vec4 vector);

	Vec4 Cross(Vec4 vector);
};
