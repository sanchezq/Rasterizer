#include "pch.h"
#include "Vec4.h"

#include <cmath>

Vec4::Vec4(float x, float y, float z, float w) :
	m_x(x), m_y(y), m_z(z), m_w(w)
{

};

Vec4::Vec4(const Vec3& vec3, float w) :
	m_w(w)
{
	m_x = vec3.m_x;
	m_y = vec3.m_y;
	m_z = vec3.m_z;
}

void Vec4::Homogenize()
{
	if (m_w != 0.f)
	{
		m_x /= m_w;
		m_y /= m_w;
		m_z /= m_w;
		m_w /= m_w;
	}
}

float Vec4::GetMagnitude() const
{
	return sqrtf(this->m_x * this->m_x + this->m_y * this->m_y + this->m_z * this->m_z);
}

void Vec4::Normalize()
{
	m_x /= GetMagnitude();
	m_y /= GetMagnitude();
	m_z /= GetMagnitude();
	//m_w /= GetMagnitude();
}

Vec4 Vec4::operator+(Vec4 vector)
{
	Vec4 nVector;
	nVector.m_x = this->m_x + vector.m_x;
	nVector.m_y = this->m_y + vector.m_y;
	nVector.m_z = this->m_z + vector.m_z;
	nVector.m_w = this->m_w + vector.m_w;

	return nVector;
}

Vec4 Vec4::operator*(float value)
{
	Vec4 nVector;
	nVector.m_x = this->m_x * value;
	nVector.m_y = this->m_y * value;
	nVector.m_z = this->m_z * value;
	nVector.m_w = this->m_w * value;

	return nVector;
}

Vec4 Vec4::operator-(Vec4 vector)
{
	Vec4 nVector;
	nVector.m_x = this->m_x - vector.m_x;
	nVector.m_y = this->m_y - vector.m_y;
	nVector.m_z = this->m_z - vector.m_z;
	nVector.m_w = this->m_w - vector.m_w;

	return nVector;
}

Vec4 Vec4::Cross(Vec4 vector)
{
	Vec4 cross;

	cross.m_x = (m_y * vector.m_z) - (m_z * vector.m_y);
	cross.m_y = (m_z * vector.m_x) - (m_x * vector.m_z);
	cross.m_z = (m_x * vector.m_y) - (m_y * vector.m_x);

	return cross;
}
