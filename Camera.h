#pragma once
#include "Mat4.h"
#include "Vec3.h"

class Camera
{
public:

	Mat4 m_transform;

	
	Vec3 m_position;
	Vec3 m_rotation;
};

