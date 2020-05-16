#pragma once

#include "Vec4.h"

class Mat4
{
public:
	Mat4();
	float t[4][4];

	Mat4 operator*(Mat4 m2); Mat4 operator*(Mat4 m2) const;
	Vec4 operator*(Vec4 v2); Vec4 operator*(Vec4 v2) const;
	Vec3 operator*(Vec3 v2); Vec3 operator*(Vec3 v2) const;
	Mat4 operator*(float value);

	Mat4 GetInverse();
	Mat4 GetTranspos();
	float GetDet();

	static Mat4 CreateTransformMatrix(const Vec3& rotation, const Vec3& position, const Vec3& scale);

private:
	static Mat4 CreateTranslationMatrix(const Vec3& translation);
	static Mat4 CreateScaleMatrix(const Vec3& scale);
	static Mat4 CreateRotationMatrix(const Vec3& rotation);
	static Mat4 CreateXRotationMatrix(float angle);
	static Mat4 CreateYRotationMatrix(float angle);
	static Mat4 CreateZRotationMatrix(float angle);

};
