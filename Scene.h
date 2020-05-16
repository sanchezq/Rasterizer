#pragma once

#include "Entity.h"
#include "Light.h"
#include <vector>

class Scene
{
public:

	Scene();
	~Scene();

	static Scene* GetInstance();

	std::vector<Entity> m_entities;
	std::vector<Light> m_lights;

private:

	static Scene* ms_instance;
};

