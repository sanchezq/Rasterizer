#include "pch.h"
#include "Light.h"

Light::Light(Vec3 pos, float ambient, float diffuse, float specular) : 
	m_position(pos), m_ambientCpnt(ambient), m_diffuseCpnt(diffuse), m_specularCpnt(specular)
{
}
