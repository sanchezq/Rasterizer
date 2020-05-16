#include "pch.h"
#include "Scene.h"

Scene* Scene::ms_instance = nullptr;

Scene::Scene()
{
	ms_instance = this;
}

Scene::~Scene()
{
	m_entities.clear();
}

Scene* Scene::GetInstance()
{
	return ms_instance;
}
