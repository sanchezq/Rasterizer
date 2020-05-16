#pragma once

#include "Vec3.h"

class Light
{
public:

	Light(Vec3 pos = { 0, 0, 0 }, float ambient = 0.f, float diffuse = 0.f, float specular = 0.f);

	Vec3 m_position;

	float m_ambientCpnt;
	float m_diffuseCpnt;
	float m_specularCpnt;

};

