#include "pch.h"
#include "Vertex.h"

Vertex::Vertex(Vec4 vector, Vec4 normale, Color color, float u, float v) :
	m_position(vector), m_normale(normale), m_color(color), m_u(u), m_v(v)
{
}
