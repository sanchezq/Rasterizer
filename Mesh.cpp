#include "pch.h"
#include "Mesh.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

Mesh::~Mesh()
{
	m_indices.clear();
	m_vertices.clear();
}

Mesh Mesh::CreateCube()
{
	Mesh newMesh;



	float size = 0.5f;

	newMesh.m_vertices.push_back(Vertex({ -size, size, size }, { 0, 0, 1 }, {255, 0, 0}, 0, 1)); //0 && 0  //devant
	newMesh.m_vertices.push_back(Vertex({ -size, size, size }, { -1, 0, 0 }, { 255, 0, 0 }, 1, 1)); //1  //gauche
	newMesh.m_vertices.push_back(Vertex({ -size, size, size }, { 0, 1, 0 }, { 255, 0, 0 }, 0, 0)); //2  //top

	newMesh.m_vertices.push_back(Vertex({ size, size, size }, {0, 0, 1}, { 255, 0, 0 }, 1, 1)); //3 && 1  //devant
	newMesh.m_vertices.push_back(Vertex({ size, size, size }, { 1, 0, 0 }, { 0, 255, 0 }, 0, 1)); //4  //droite
	newMesh.m_vertices.push_back(Vertex({ size, size, size }, { 0, 1, 0 }, { 0, 255, 0 }, 1, 0)); //5  //top

	newMesh.m_vertices.push_back(Vertex({ size, -size, size }, { 0, 0, 1 }, { 255, 0, 0 }, 1, 0)); //6 && 2  //devant
	newMesh.m_vertices.push_back(Vertex({ size, -size, size }, { 1, 0, 0 }, { 0, 0, 255 }, 0, 0)); //7  //droite
	newMesh.m_vertices.push_back(Vertex({ size, -size, size }, { 0, -1, 0 }, { 0, 0, 255 }, 1, 1)); //8  //bottom

	newMesh.m_vertices.push_back(Vertex({ -size, -size, size }, { 0, 0, 1 }, { 255, 0, 0 }, 0, 0)); //9 && 3  //devant
	newMesh.m_vertices.push_back(Vertex({ -size, -size, size }, { -1, 0, 0 }, { 255, 255, 0 }, 1, 0)); //10  //gauche
	newMesh.m_vertices.push_back(Vertex({ -size, -size, size }, { 0, -1, 0 }, { 255, 255, 0 }, 0, 1)); //11  //bottom

	newMesh.m_vertices.push_back(Vertex({ -size, size, -size }, { 0, 0, -1 }, { 0, 255, 255 }, 1, 1)); //12 && 4  //derriere
	newMesh.m_vertices.push_back(Vertex({ -size, size, -size }, { -1, 0, 0 }, { 0, 255, 255 }, 0, 1)); //13  //gauche
	newMesh.m_vertices.push_back(Vertex({ -size, size, -size }, { 0, 1, 0 }, { 0, 255, 255 }, 0, 1)); //14  //top

	newMesh.m_vertices.push_back(Vertex({ size, size, -size }, { 1, 0, 0 }, { 255, 0, 255 }, 1, 1)); //15 && 5  //droite
	newMesh.m_vertices.push_back(Vertex({ size, size, -size }, { 0, 0, -1 }, { 255, 0, 255 }, 0, 1)); //16  //derriere
	newMesh.m_vertices.push_back(Vertex({ size, size, -size }, { 0, 1, 0 }, { 255, 0, 255 }, 1, 1)); //17  //top

	newMesh.m_vertices.push_back(Vertex({ size, -size, -size }, { 1, 0, 0 }, { 255, 127, 255 }, 1, 0)); //18 && 6  //droite
	newMesh.m_vertices.push_back(Vertex({ size, -size, -size }, { 0, 0, -1 }, { 255, 127, 255 }, 0, 0)); //19  //derriere
	newMesh.m_vertices.push_back(Vertex({ size, -size, -size }, { 0, -1, 0 }, { 255, 127, 255 }, 1, 0)); //20  //bottom

	newMesh.m_vertices.push_back(Vertex({ -size, -size, -size }, { 0, 0, -1 }, { 255, 127, 127 }, 1, 0)); //21 && 7  //derriere
	newMesh.m_vertices.push_back(Vertex({ -size, -size, -size }, { -1, 0, 0 }, { 255, 127, 127 }, 0, 0)); //22  //gauche
	newMesh.m_vertices.push_back(Vertex({ -size, -size, -size }, { 0, -1, 0 }, { 255, 127, 127 }, 0, 0)); //23  //bottom


	newMesh.m_indices.push_back(0);
	newMesh.m_indices.push_back(6);
	newMesh.m_indices.push_back(3);
	//devant
	newMesh.m_indices.push_back(0);
	newMesh.m_indices.push_back(9);
	newMesh.m_indices.push_back(6);



	newMesh.m_indices.push_back(4);
	newMesh.m_indices.push_back(18);
	newMesh.m_indices.push_back(15);
	//droite
	newMesh.m_indices.push_back(4);
	newMesh.m_indices.push_back(7);
	newMesh.m_indices.push_back(18);



	newMesh.m_indices.push_back(16);
	newMesh.m_indices.push_back(21);
	newMesh.m_indices.push_back(12);
	//derriere
	newMesh.m_indices.push_back(16);
	newMesh.m_indices.push_back(19);
	newMesh.m_indices.push_back(21);



	newMesh.m_indices.push_back(13);
	newMesh.m_indices.push_back(10);
	newMesh.m_indices.push_back(1);
	//gauche
	newMesh.m_indices.push_back(13);
	newMesh.m_indices.push_back(22);
	newMesh.m_indices.push_back(10);



	newMesh.m_indices.push_back(11);
	newMesh.m_indices.push_back(20);
	newMesh.m_indices.push_back(8);
	//bottom
	newMesh.m_indices.push_back(11);
	newMesh.m_indices.push_back(23);
	newMesh.m_indices.push_back(20);



	newMesh.m_indices.push_back(2);
	newMesh.m_indices.push_back(5);
	newMesh.m_indices.push_back(17);
	//top
	newMesh.m_indices.push_back(2);
	newMesh.m_indices.push_back(17);
	newMesh.m_indices.push_back(14);

	return newMesh;


}

Mesh Mesh::CreateSphere(int latitudeCount, int longitudeCount)
{
	Mesh newMesh;

	float latitude_increment = 360.0f / latitudeCount;
	float longitude_increment = 180.0f / longitudeCount;

	for (float u = 0; u < 360.0f; u += latitude_increment) {

		for (float t = 0; t < 180.0f; t += longitude_increment) {

			float rad = 1.f;

			float x = (float)(rad * sin(t * (M_PI / 180)) * sin(u * (M_PI / 180)));
			float y = (float)(rad * cos(t * (M_PI / 180)));
			float z = (float)(rad * sin(t * (M_PI / 180)) * cos(u * (M_PI / 180)));

			Vertex v0({ x, y, z });
			if (newMesh.m_vertices.size() != 0)
			{
				v0.m_normale = v0.m_position;
				v0.m_normale.Normalize();
			}
			newMesh.m_vertices.push_back(v0);

			float x1 = (float)(rad * sin((t + longitude_increment) * (M_PI / 180)) * sin((u + latitude_increment) * (M_PI / 180)));
			float y1 = (float)(rad * cos((t + longitude_increment) * (M_PI / 180)));
			float z1 = (float)(rad * sin((t + longitude_increment) * (M_PI / 180)) * cos((u + latitude_increment) * (M_PI / 180)));

			Vertex v1({ x1, y1, z1 });
			v1.m_normale = v1.m_position;
			v1.m_normale.Normalize();

			newMesh.m_vertices.push_back(v1);

		}
	}


	for (int i = 0; i < newMesh.m_vertices.size() - 2; i++)
	{
		newMesh.m_indices.push_back(i);
		newMesh.m_indices.push_back(i + 2);
		newMesh.m_indices.push_back(i + 1);

		i++;
		if (i < newMesh.m_vertices.size() - 2)
		{
			newMesh.m_indices.push_back(i);
			newMesh.m_indices.push_back(i + 1);
			newMesh.m_indices.push_back(i + 2);
		}
	}

	return newMesh;
}

Mesh Mesh::CreateObject(const std::string& filename)
{
	Mesh mesh;

	std::vector<Vec4> points;
	std::vector<Vec3> normales;
	

	std::string line;
	std::ifstream ifi(filename);

	if (!ifi.is_open())
	{
		std::cout << "Error opening file" << std::endl;
		return mesh;
	}
	else
	{
		while (getline(ifi, line))
		{
			if (line.empty())
			{
				continue;
			}

			std::istringstream keywordLineStream(line);

			std::string keyboard;
			keywordLineStream >> keyboard;

		//	std::cout << keyboard << '\n';

			if (keyboard == "#")
			{
				continue;
			}
			else if (keyboard == "v")
			{
				Vec4 vec;
				std::string val = line.substr(2);
				sscanf_s(val.c_str(), "%f %f %f", &vec.m_x, &vec.m_y, &vec.m_z);

				points.push_back(vec);
			}
			else if (keyboard == "vn")
			{
				Vec3 norm;
				std::string val = line.substr(2);
				sscanf_s(val.c_str(), "%f %f %f", &norm.m_x, &norm.m_y, &norm.m_z);

				normales.push_back(norm);
			}
			else if (keyboard == "f")
			{
				int v0Vec, v1Vec, v2Vec, v0Norm, v1Norm, v2Norm;
				std::string val = line.substr(2);
				sscanf_s(val.c_str(), "%d//%d %d//%d %d//%d", &v0Vec, &v0Norm, &v1Vec, &v1Norm, &v2Vec, &v2Norm);

				if (v0Vec < 0)
				{
					v0Vec = (int)points.size() + v0Vec +1;
				}
				if (v0Norm < 0)
				{
					v0Norm = (int)normales.size() + v0Norm +1;
				}
				if (v1Vec < 0)
				{
					v1Vec = (int)points.size() + v1Vec +1;
				}
				if (v1Norm < 0)
				{
					v1Norm = (int)normales.size() + v1Norm +1;
				}
				if (v2Vec < 0)
				{
					v2Vec = (int)points.size() + v2Vec +1;
				}
				if (v2Norm < 0)
				{
					v2Norm = (int)normales.size() + v2Norm +1;
				}

				Vertex v0{ points[(size_t)v0Vec-1], normales[(size_t)v0Norm-1] };
				Vertex v1{ points[(size_t)v1Vec-1], normales[(size_t)v1Norm-1] };
				Vertex v2{ points[(size_t)v2Vec-1], normales[(size_t)v2Norm-1] };

				mesh.m_indices.push_back((int)mesh.m_vertices.size());
				mesh.m_vertices.push_back(v0);
				mesh.m_indices.push_back((int)mesh.m_vertices.size());
				mesh.m_vertices.push_back(v1);
				mesh.m_indices.push_back((int)mesh.m_vertices.size());
				mesh.m_vertices.push_back(v2);
			}

		}
	}

	return mesh;
}

