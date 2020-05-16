#pragma once

#include "Vertex.h"
#include "Texture.h"
#include <vector>
#include <string>

class Mesh
{
public:

	~Mesh();
	

	static Mesh CreateCube();
	static Mesh CreateSphere(int latitudeCount, int longitudeCount);
	static Mesh CreateObject(const std::string& filename);

	std::vector<Vertex> m_vertices;
	std::vector<int> m_indices;
	Texture* pTexture = nullptr;



};

