#pragma once
#include "Mesh.h"
#include "Mat4.h"

class Entity
{
public:
	Mesh* m_mesh = nullptr;
	Mat4 m_transformation;

	Mat4 m_normaleTransform;
	float m_alpha;
};
