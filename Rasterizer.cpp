#include "pch.h"

#include <iostream>

#include "Rasterizer.h"
#include "Triangle.h"

#define _USE_MATH_DEFINES
#include "math.h"


Rasterizer* Rasterizer::ms_instance = nullptr;

Rasterizer::Rasterizer()
{
	ms_instance = this;
}

float a = 3.f;
bool b = true;
float c = -10.f;

void Rasterizer::RendererScene(Scene * pScene, Texture * pTarget, const Mat4& projectionMatrix, const Mat4& inverseCameraMatrix, bool wireframe, bool backface, Camera camera)
{
	pTarget->ResetPixelColor();

	Vertex v0({ 0, 0, 0 });
	Vertex v1({ 0, 0, 0 });
	Vertex v2({ 0, 0, 0 });

	Vertex vLTN({ -5.f, 5.f, .1f });
	Vertex vRBF({ 5.f, -5.f, 4.5f });

	vLTN.m_position.m_x = ((vLTN.m_position.m_x / 5) + 1) * 0.5f * pTarget->GetWidth();
	vRBF.m_position.m_x = ((vRBF.m_position.m_x / 5) + 1) * 0.5f * pTarget->GetWidth();
	vLTN.m_position.m_y = ((vLTN.m_position.m_y / 5) + 1) * 0.5f * pTarget->GetHeight();
	vRBF.m_position.m_y = ((vRBF.m_position.m_y / 5) + 1) * 0.5f * pTarget->GetHeight();
	
	for (auto& entity : pScene->m_entities)
	{

		for (int i = 0; i < entity.m_mesh->m_indices.size(); i += 3)
		{
			v0 = entity.m_mesh->m_vertices[entity.m_mesh->m_indices[i]];
			v1 = entity.m_mesh->m_vertices[entity.m_mesh->m_indices[(size_t)(i + 1)]];
			v2 = entity.m_mesh->m_vertices[entity.m_mesh->m_indices[(size_t)(i + 2)]];

			v0.m_position = projectionMatrix * inverseCameraMatrix * entity.m_transformation * v0.m_position;
			v1.m_position = projectionMatrix * inverseCameraMatrix * entity.m_transformation * v1.m_position;
			v2.m_position = projectionMatrix * inverseCameraMatrix * entity.m_transformation * v2.m_position;

			// Viewport
			v0.m_position.m_x = ((v0.m_position.m_x / 5) + 1) * 0.5f * pTarget->GetWidth();
			v1.m_position.m_x = ((v1.m_position.m_x / 5) + 1) * 0.5f * pTarget->GetWidth();
			v2.m_position.m_x = ((v2.m_position.m_x / 5) + 1) * 0.5f * pTarget->GetWidth();
			v0.m_position.m_y = ((v0.m_position.m_y / 5) + 1) * 0.5f * pTarget->GetHeight();
			v1.m_position.m_y = ((v1.m_position.m_y / 5) + 1) * 0.5f * pTarget->GetHeight();
			v2.m_position.m_y = ((v2.m_position.m_y / 5) + 1) * 0.5f * pTarget->GetHeight();

			v0.m_color.m_a = (unsigned char)(v0.m_color.m_a * entity.m_alpha);
			v1.m_color.m_a = (unsigned char)(v1.m_color.m_a * entity.m_alpha);
			v2.m_color.m_a = (unsigned char)(v2.m_color.m_a * entity.m_alpha);

			Mat4 trans = projectionMatrix * entity.m_normaleTransform;

			Triangle triangle(v0, v1, v2, *pTarget, *pScene, trans, camera, entity.m_mesh->pTexture);
			triangle.RenderTriangle(vLTN, vRBF, wireframe, backface);
		}
	}
}

Rasterizer* Rasterizer::GetInstance()
{
	return ms_instance;
}

Mat4 Rasterizer::CreatePerspectiveProjectionMatrix(int width, int height, float near, float far, float fov)
{
	Mat4 mat;

	int imageAspectRatio = width / height;
	float b, t, l, r;

	float scale = (float)tan(fov * 0.5 * M_PI / 180) * near;
	r = (float)imageAspectRatio * scale, l = -r;

	t = scale, b = -t;


	mat.t[0][0] = near / r;
	mat.t[1][1] = near / t;
	mat.t[2][2] = -(far + near) / (far - near);
	mat.t[2][3] = (-2 * far * near) / (far - near);
	mat.t[3][2] = -1;
	mat.t[3][3] = near;

	return mat;
}