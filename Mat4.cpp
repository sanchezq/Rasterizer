#include "pch.h"
#include "Mat4.h"
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

Mat4::Mat4()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			t[j][i] = 0.f;

			if (j == i)
			{
				t[j][i] = 1.f;
			}
		}
	}
}

Mat4 Mat4::operator*(Mat4 m2)
{
	Mat4 mat;

	for (int i = 0; i < 4; i++)
	{
			for (int j = 0; j < 4; j++)
			{
				float a = 0;

				for (int k = 0; k < 4; k++)
				{
					a += t[k][i] * m2.t[j][k];
				}

				mat.t[j][i] = a;
			}
	}

	return mat;
}

Mat4 Mat4::operator*(Mat4 m2) const
{
	Mat4 mat;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float a = 0;

			for (int k = 0; k < 4; k++)
			{
				a += t[k][i] * m2.t[j][k];
			}

			mat.t[j][i] = a;
		}
	}

	return mat;
}

Vec4 Mat4::operator*(Vec4 v2)
{
	Vec4 vec;

	vec.m_x = t[0][0] * v2.m_x + t[1][0] * v2.m_y + t[2][0] * v2.m_z + t[3][0] * v2.m_w;
	vec.m_y = t[0][1] * v2.m_x + t[1][1] * v2.m_y + t[2][1] * v2.m_z + t[3][1] * v2.m_w;
	vec.m_z = t[0][2] * v2.m_x + t[1][2] * v2.m_y + t[2][2] * v2.m_z + t[3][2] * v2.m_w;
	vec.m_w = t[0][3] * v2.m_x + t[1][3] * v2.m_y + t[2][3] * v2.m_z + t[3][3] * v2.m_w;

	if(vec.m_w > 0)
		vec.Homogenize();

	return vec;
}


Vec4 Mat4::operator*(Vec4 v2) const
{
	Vec4 vec;

	vec.m_x = t[0][0] * v2.m_x + t[1][0] * v2.m_y + t[2][0] * v2.m_z + t[3][0] * v2.m_w;
	vec.m_y = t[0][1] * v2.m_x + t[1][1] * v2.m_y + t[2][1] * v2.m_z + t[3][1] * v2.m_w;
	vec.m_z = t[0][2] * v2.m_x + t[1][2] * v2.m_y + t[2][2] * v2.m_z + t[3][2] * v2.m_w;
	vec.m_w = t[0][3] * v2.m_x + t[1][3] * v2.m_y + t[2][3] * v2.m_z + t[3][3] * v2.m_w;

	if (vec.m_w > 0)
		vec.Homogenize();

	return vec;
}

Vec3 Mat4::operator*(Vec3 v2)
{
	Vec3 vec;

	vec.m_x = t[0][0] * v2.m_x + t[1][0] * v2.m_y + t[2][0] * v2.m_z + t[3][0] * 1;
	vec.m_y = t[0][1] * v2.m_x + t[1][1] * v2.m_y + t[2][1] * v2.m_z + t[3][1] * 1;
	vec.m_z = t[0][2] * v2.m_x + t[1][2] * v2.m_y + t[2][2] * v2.m_z + t[3][2] * 1;

	return vec;
}

Vec3 Mat4::operator*(Vec3 v2) const
{
	Vec3 vec;

	vec.m_x = t[0][0] * v2.m_x + t[1][0] * v2.m_y + t[2][0] * v2.m_z + t[3][0] * 1;
	vec.m_y = t[0][1] * v2.m_x + t[1][1] * v2.m_y + t[2][1] * v2.m_z + t[3][1] * 1;
	vec.m_z = t[0][2] * v2.m_x + t[1][2] * v2.m_y + t[2][2] * v2.m_z + t[3][2] * 1;

	return vec;
}

Mat4 Mat4::operator*(float value)
{
	Mat4 mat;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat.t[i][j] = t[i][j] * value;
		}
	}

	return mat;
}

Mat4 Mat4::GetInverse()
{
	Mat4 inverse;

	inverse.t[0][0] = t[1][2] * t[2][3] * t[3][1] - t[1][3] * t[2][2] * t[3][1] + t[1][3] * t[2][1] * t[3][2] - t[1][1] * t[2][3] * t[3][2] - t[1][2] * t[2][1] * t[3][3] + t[1][1] * t[2][2] * t[3][3];
	inverse.t[0][1] = t[0][3] * t[2][2] * t[3][1] - t[0][2] * t[2][3] * t[3][1] - t[0][3] * t[2][1] * t[3][2] + t[0][1] * t[2][3] * t[3][2] + t[0][2] * t[2][1] * t[3][3] - t[0][1] * t[2][2] * t[3][3];
	inverse.t[0][2] = t[0][2] * t[1][3] * t[3][1] - t[0][3] * t[1][2] * t[3][1] + t[0][3] * t[1][1] * t[3][2] - t[0][1] * t[1][3] * t[3][2] - t[0][2] * t[1][1] * t[3][3] + t[0][1] * t[1][2] * t[3][3];
	inverse.t[0][3] = t[0][3] * t[1][2] * t[2][1] - t[0][2] * t[1][3] * t[2][1] - t[0][3] * t[1][1] * t[2][2] + t[0][1] * t[1][3] * t[2][2] + t[0][2] * t[1][1] * t[2][3] - t[0][1] * t[1][2] * t[2][3];
	inverse.t[1][0] = t[1][3] * t[2][2] * t[3][0] - t[1][2] * t[2][3] * t[3][0] - t[1][3] * t[2][0] * t[3][2] + t[1][0] * t[2][3] * t[3][2] + t[1][2] * t[2][0] * t[3][3] - t[1][0] * t[2][2] * t[3][3];
	inverse.t[1][1] = t[0][2] * t[2][3] * t[3][0] - t[0][3] * t[2][2] * t[3][0] + t[0][3] * t[2][0] * t[3][2] - t[0][0] * t[2][3] * t[3][2] - t[0][2] * t[2][0] * t[3][3] + t[0][0] * t[2][2] * t[3][3];
	inverse.t[1][2] = t[0][3] * t[1][2] * t[3][0] - t[0][2] * t[1][3] * t[3][0] - t[0][3] * t[1][0] * t[3][2] + t[0][0] * t[1][3] * t[3][2] + t[0][2] * t[1][0] * t[3][3] - t[0][0] * t[1][2] * t[3][3];
	inverse.t[1][3] = t[0][2] * t[1][3] * t[2][0] - t[0][3] * t[1][2] * t[2][0] + t[0][3] * t[1][0] * t[2][2] - t[0][0] * t[1][3] * t[2][2] - t[0][2] * t[1][0] * t[2][3] + t[0][0] * t[1][2] * t[2][3];
	inverse.t[2][0] = t[1][1] * t[2][3] * t[3][0] - t[1][3] * t[2][1] * t[3][0] + t[1][3] * t[2][0] * t[3][1] - t[1][0] * t[2][3] * t[3][1] - t[1][1] * t[2][0] * t[3][3] + t[1][0] * t[2][1] * t[3][3];
	inverse.t[2][1] = t[0][3] * t[2][1] * t[3][0] - t[0][1] * t[2][3] * t[3][0] - t[0][3] * t[2][0] * t[3][1] + t[0][0] * t[2][3] * t[3][1] + t[0][1] * t[2][0] * t[3][3] - t[0][0] * t[2][1] * t[3][3];
	inverse.t[2][2] = t[0][1] * t[1][3] * t[3][0] - t[0][3] * t[1][1] * t[3][0] + t[0][3] * t[1][0] * t[3][1] - t[0][0] * t[1][3] * t[3][1] - t[0][1] * t[1][0] * t[3][3] + t[0][0] * t[1][1] * t[3][3];
	inverse.t[2][3] = t[0][3] * t[1][1] * t[2][0] - t[0][1] * t[1][3] * t[2][0] - t[0][3] * t[1][0] * t[2][1] + t[0][0] * t[1][3] * t[2][1] + t[0][1] * t[1][0] * t[2][3] - t[0][0] * t[1][1] * t[2][3];
	inverse.t[3][0] = t[1][2] * t[2][1] * t[3][0] - t[1][1] * t[2][2] * t[3][0] - t[1][2] * t[2][0] * t[3][1] + t[1][0] * t[2][2] * t[3][1] + t[1][1] * t[2][0] * t[3][2] - t[1][0] * t[2][1] * t[3][2];
	inverse.t[3][1] = t[0][1] * t[2][2] * t[3][0] - t[0][2] * t[2][1] * t[3][0] + t[0][2] * t[2][0] * t[3][1] - t[0][0] * t[2][2] * t[3][1] - t[0][1] * t[2][0] * t[3][2] + t[0][0] * t[2][1] * t[3][2];
	inverse.t[3][2] = t[0][2] * t[1][1] * t[3][0] - t[0][1] * t[1][2] * t[3][0] - t[0][2] * t[1][0] * t[3][1] + t[0][0] * t[1][2] * t[3][1] + t[0][1] * t[1][0] * t[3][2] - t[0][0] * t[1][1] * t[3][2];
	inverse.t[3][3] = t[0][1] * t[1][2] * t[2][0] - t[0][2] * t[1][1] * t[2][0] + t[0][2] * t[1][0] * t[2][1] - t[0][0] * t[1][2] * t[2][1] - t[0][1] * t[1][0] * t[2][2] + t[0][0] * t[1][1] * t[2][2];
	
	inverse * (1 / inverse.GetDet());

	return inverse;
}

Mat4 Mat4::GetTranspos()
{
	Mat4 transpos;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			transpos.t[j][i] = t[i][j];
		}
	}

	return transpos;
}

float Mat4::GetDet()
{
	float value = t[0][3] * t[1][2] * t[2][1] * t[3][0] - t[0][2] * t[1][3] * t[2][1] * t[3][0] - t[0][3] * t[1][1] * t[2][2] * t[3][0] + t[0][1] * t[1][3] * t[2][2] * t[3][0] +
		t[0][2] * t[1][1] * t[2][3] * t[3][0] - t[0][1] * t[1][2] * t[2][3] * t[3][0] - t[0][3] * t[1][2] * t[2][0] * t[3][1] + t[0][2] * t[1][3] * t[2][0] * t[3][1] +
		t[0][3] * t[1][0] * t[2][2] * t[3][1] - t[0][0] * t[1][3] * t[2][2] * t[3][1] - t[0][2] * t[1][0] * t[2][3] * t[3][1] + t[0][0] * t[1][2] * t[2][3] * t[3][1] +
		t[0][3] * t[1][1] * t[2][0] * t[3][2] - t[0][1] * t[1][3] * t[2][0] * t[3][2] - t[0][3] * t[1][0] * t[2][1] * t[3][2] + t[0][0] * t[1][3] * t[2][1] * t[3][2] +
		t[0][1] * t[1][0] * t[2][3] * t[3][2] - t[0][0] * t[1][1] * t[2][3] * t[3][2] - t[0][2] * t[1][1] * t[2][0] * t[3][3] + t[0][1] * t[1][2] * t[2][0] * t[3][3] +
		t[0][2] * t[1][0] * t[2][1] * t[3][3] - t[0][0] * t[1][2] * t[2][1] * t[3][3] - t[0][1] * t[1][0] * t[2][2] * t[3][3] + t[0][0] * t[1][1] * t[2][2] * t[3][3];

	return value;
}


Mat4 Mat4::CreateTransformMatrix(const Vec3& rotation, const Vec3& position, const Vec3& scale)
{
	Mat4 mat;

	mat = CreateTranslationMatrix(position) * CreateScaleMatrix(scale) * CreateRotationMatrix(rotation);
	
	return mat;
}

Mat4 Mat4::CreateTranslationMatrix(const Vec3& translation)
{
	Mat4 mat;

	mat.t[3][0] = translation.m_x;
	mat.t[3][1] = translation.m_y;
	mat.t[3][2] = translation.m_z;

	return mat;
}

Mat4 Mat4::CreateScaleMatrix(const Vec3& scale)
{
	Mat4 mat;

	mat.t[0][0] = scale.m_x;
	mat.t[1][1] = scale.m_y;
	mat.t[2][2] = scale.m_z;

	return mat;
}

Mat4 Mat4::CreateRotationMatrix(const Vec3& rotation)
{
	Mat4 mat;

	mat = CreateXRotationMatrix(rotation.m_x) * CreateYRotationMatrix(rotation.m_y) * CreateZRotationMatrix(rotation.m_z);
	
	return mat;
}

Mat4 Mat4::CreateXRotationMatrix(float angle)
{
	angle = ((float)M_PI / 180) * angle;

	Mat4 mat;

	mat.t[1][1] = cos(angle);
	mat.t[1][2] = -sin(angle);
	mat.t[2][1] = sin(angle);
	mat.t[2][2] = cos(angle);

	return mat;
}

Mat4 Mat4::CreateYRotationMatrix(float angle)
{
	angle = ((float)M_PI / 180) * angle;

	Mat4 mat;

	mat.t[0][0] = cos(angle);
	mat.t[0][2] = sin(angle);
	mat.t[2][0] = -sin(angle);
	mat.t[2][2] = cos(angle);

	return mat;
}

Mat4 Mat4::CreateZRotationMatrix(float angle)
{
	angle = ((float)M_PI / 180) * angle;

	Mat4 mat;

	mat.t[0][0] = cos(angle);
	mat.t[0][1] = -sin(angle);
	mat.t[1][0] = sin(angle);
	mat.t[1][1] = cos(angle);

	return mat;
}
