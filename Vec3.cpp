#include "pch.h"
#include "Vec3.h"

#include <cmath>

Vec3::Vec3(float x, float y, float z) :
	m_x(x), m_y(y), m_z(z)
{

};

float Vec3::GetMagnitude()
{
	return sqrtf(this->m_x * this->m_x + this->m_y * this->m_y + this->m_z * this->m_z);
}

void Vec3::Normalize()
{
	m_x /= GetMagnitude();
	m_y /= GetMagnitude();
	m_z /= GetMagnitude();
}

Vec3 Vec3::operator+(Vec3 vector)
{
	Vec3 nVector;
	nVector.m_x = this->m_x + vector.m_x;
	nVector.m_y = this->m_y + vector.m_y;
	nVector.m_z = this->m_z + vector.m_z;

	return nVector;
}

Vec3 Vec3::operator*(float value)
{
	Vec3 nVector;
	nVector.m_x = this->m_x * value;
	nVector.m_y = this->m_y * value;
	nVector.m_z = this->m_z * value;

	return nVector;
}

Vec3 Vec3::operator-(Vec3 vector)
{
	Vec3 nVector;
	nVector.m_x = this->m_x - vector.m_x;
	nVector.m_y = this->m_y - vector.m_y;
	nVector.m_z = this->m_z - vector.m_z;

	return nVector;
}
