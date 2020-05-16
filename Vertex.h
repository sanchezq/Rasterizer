#pragma once

#include "Vec4.h"
#include "Color.h"

struct Vertex
{
	Vertex(Vec4 vector, Vec4 normale = Vec4(0, 0, 0), Color color = Color(255, 255, 255), float u = 0.f, float v = 0.f);

	float m_u;
	float m_v;

	Vec4 m_position;
	Color m_color;
	Vec4 m_normale;
};

