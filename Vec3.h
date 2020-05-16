#pragma once
class Vec3
{
public:

	Vec3(float x = 0.f, float y = 0.f, float z = 0.f);

	float m_x;
	float m_y;
	float m_z;

	float GetMagnitude();
	void Normalize();

	Vec3 operator+(Vec3 vector);
	Vec3 operator*(float value);
	Vec3 operator-(Vec3 vector);
};

