#pragma once

#include <vector>
#include "Vertex.h"
#include "Texture.h"
#include "Scene.h"
#include "Mat4.h"
#include "Camera.h"

class Triangle
{
public:

	Triangle(Vertex v0, Vertex v1, Vertex v2, Texture& Target, Scene& Scene, Mat4& transform, Camera camera, Texture* texture = nullptr);

	void RenderTriangle(Vertex leftTopNearScreen, Vertex rightBotFarScreen, bool wireframe, bool backface);
	void DrawTriangleSides(Vec3 v0, Vec3 v1, Vec3 v2);
	void BarycentricAlgorithm(Vec3 v0, Vec3 v1, Vec3 v2);
	void Bresenham(Vec3 v0, Vec3 v1);
	void CheckBarycentre(int x, int y);

	float CheckLight(float W1, float W2, float W3);
	float CheckZ(float W1, float W2, float W3);
	float CheckAlpha(float W1, float W2, float W3);
	Color CheckColor(float W1, float W2, float W3);

	bool isBackFace();

	std::vector<Vec3> m_points;

	Vertex v0;
	Vertex v1;
	Vertex v2;

	Texture& pTarget;
	Scene& pScene;
	Texture* m_texture;
	Mat4& m_tranformation;
	Camera m_camera;

};

