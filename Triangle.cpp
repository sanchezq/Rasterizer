#include "pch.h"
#include "Triangle.h"
#include "Suth-Hodg.h"
#include "Vertex.h"
#include "Vec3.h"

#include <cmath>

Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2, Texture& Target, Scene& Scene, Mat4& transform, Camera camera, Texture* texture) :
	pTarget(Target), pScene(Scene), m_tranformation(transform), m_texture(texture), m_camera(camera), v1(v1), v2(v2), v0(v0)
{

	m_points.push_back({ v0.m_position.m_x, v0.m_position.m_y, v0.m_position.m_z });
	m_points.push_back({ v1.m_position.m_x, v1.m_position.m_y, v1.m_position.m_z });
	m_points.push_back({ v2.m_position.m_x, v2.m_position.m_y, v2.m_position.m_z });


}

void Triangle::RenderTriangle(Vertex leftTopNearScreen, Vertex rightBotFarScreen, bool wireframe, bool backface)
{
	m_points = PixelClipping(leftTopNearScreen, rightBotFarScreen, m_points);



	if (wireframe)
	{
		for (int i = 2; i < m_points.size(); i++)
		{
			DrawTriangleSides(m_points[0], m_points[i], m_points[i - 1]);
		}
	}
	else
	{
		if (backface)
		{
			if (!isBackFace() || pScene.m_lights.size() == 0)
			{
				return;
			}
		}
		else if (pScene.m_lights.size() == 0)
		{
			return;
		}

		for (int i = 2; i < m_points.size(); i++)
		{
			BarycentricAlgorithm(m_points[0], m_points[i], m_points[i - 1]);
		}
	}
}

void Triangle::DrawTriangleSides(Vec3 v0, Vec3 v1, Vec3 v2)
{
	Bresenham(v0, v1);
	Bresenham(v1, v2);
	Bresenham(v2, v0);
}

void Triangle::BarycentricAlgorithm(Vec3 v1, Vec3 v2, Vec3 v3)
{
	int maxX = (int)(std::fmax(v1.m_x, std::fmax(v2.m_x, v3.m_x)));
	int minX = (int)(std::fmin(v1.m_x, std::fmin(v2.m_x, v3.m_x)));
	int maxY = (int)(std::fmax(v1.m_y, std::fmax(v2.m_y, v3.m_y)));
	int minY = (int)(std::fmin(v1.m_y, std::fmin(v2.m_y, v3.m_y)));

	Vec3 vs1( (v2.m_x - v1.m_x), (v2.m_y - v1.m_y), 0 );
	Vec3 vs2( (v3.m_x - v1.m_x), (v3.m_y - v1.m_y), 0 );

	for (float x = (float)minX; x <= (float)maxX; x++)
	{
		for (float y = (float)minY; y <= (float)maxY; y++)
		{
			Vec3 q(x - v1.m_x, y - v1.m_y, 0);

			float s = ((float)(q.m_x * vs2.m_y) - (float)(vs2.m_x * q.m_y)) / ((float)(vs1.m_x * vs2.m_y) - (float)(vs2.m_x * vs1.m_y));
			float t = ((float)(vs1.m_x * q.m_y) - (float)(q.m_x * vs1.m_y)) / ((float)(vs1.m_x * vs2.m_y) - (float)(vs2.m_x * vs1.m_y));

			if ((s >= 0) && (t >= 0) && (s + t <= 1))
			{
				CheckBarycentre((int)x, (int)y);
			}
		}
	}
}

void Triangle::Bresenham(Vec3 v0, Vec3 v1)
{
	bool changed = false;
	int x = (int)v0.m_x;
	int y = (int)v0.m_y;
	
	int dx = (int)v1.m_x - (int)v0.m_x;
	int dy = (int)v1.m_y - (int)v0.m_y;

	int stepX = (dx > 0 ? 1 : -1);
	dx *= stepX;
	int stepY = (dy > 0 ? 1 : -1);
	dy *= stepY;

	if (dy > dx)
	{
		std::swap(dx, dy);
		changed = true;
	}

	float e = 2 * (float)dy - (float)dx;

	for (int i = 1; i <= dx; i++)
	{
		pTarget.SetWireframePixelColor(x, y, { 255, 255, 255 });
		if (e >= 0)
		{
			if (changed)
			{
				x = x + stepX;
			}
			else
			{
				y = y + stepY;
			}
				e = e - 2 * dx;
		}
		if (changed)
		{
			y += stepY;
		}
		else
		{
			x += stepX;
		}
		e = e + 2 * dy;
	}
}

void Triangle::CheckBarycentre(int x, int y)
{
	//CHECK BARYCENTRE
	float denom = ((v1.m_position.m_y - v2.m_position.m_y) * (v0.m_position.m_x - v2.m_position.m_x) + (v2.m_position.m_x - v1.m_position.m_x) * (v0.m_position.m_y - v2.m_position.m_y));

	float W1 = ((v1.m_position.m_y - v2.m_position.m_y) * (x - v2.m_position.m_x) + (v2.m_position.m_x - v1.m_position.m_x) * (y - v2.m_position.m_y)) / denom;
	float W2 = ((v2.m_position.m_y - v0.m_position.m_y) * (x - v2.m_position.m_x) + (v0.m_position.m_x - v2.m_position.m_x) * (y - v2.m_position.m_y)) / denom;
	float W3 = 1 - W1 - W2;

	if (W1 < 0 || W2 < 0 || W3 < 0)
	{
		W1 = 0;
		W2 = 0;
		W3 = 0;
	}


	//CHECK Z
	float z = CheckZ(W1, W2, W3);

	//CHECK ZBuffer
	int i = (int)(y * pTarget.GetWidth()) + x;

	if ((unsigned int)i > (pTarget.GetWidth()* pTarget.GetHeight()))
	{
		return;
	}

	if (pTarget.GetZBuffer()[i] > -z)
	{
		return;
	}
	pTarget.GetZBuffer()[i] = -z;



	//CHECK NORMALE

	float I = CheckLight(W1, W2, W3);

	//float I = 1.f;

	//CHECK COLOR

	Color color = CheckColor(W1, W2, W3);

	//Check Alpha
	float alpha = CheckAlpha(W1, W2, W3);

	pTarget.SetPixelColor(x, y, { (unsigned char)(color.m_r*I), (unsigned char)(color.m_g*I), (unsigned char)(color.m_b*I) }, alpha, i);

}

float Triangle::CheckLight(float W1, float W2, float W3)
{
	Vec4 normaleOrigin = (v0.m_normale * W1) + (v1.m_normale * W2) + (v2.m_normale * W3);
	normaleOrigin.Normalize();
	Mat4 normaleTransform = (m_tranformation.GetInverse()).GetTranspos();
	Vec4 normale = normaleTransform * normaleOrigin;
	normale.Normalize();

	float Ia = 0, Id = 0, Is = 0, I = 0;
	Vec3 V(0, 0, 0);


	for (int i = 0; i < pScene.m_lights.size(); i++)
	{
		Light light = pScene.m_lights[i];
		

		Ia += light.m_ambientCpnt;

		float dotd = light.m_position.m_x * normale.m_x + light.m_position.m_y * normale.m_y + light.m_position.m_z * normale.m_z;
		Id += light.m_diffuseCpnt * dotd;

		Vec3 H = light.m_position + V;
		H.Normalize();

		float dots = normale.m_x * H.m_x + normale.m_y * H.m_y + normale.m_z * H.m_z;
		Is += light.m_specularCpnt * dots;
	}

	I = Ia + Id + Is;

	if (I < 0)
	{
		I = 0.1f;
	}
	else if (I > 1)
	{
		I = 1.f;
	}

	return I;
}

float Triangle::CheckZ(float W1, float W2, float W3)
{
	return W1 * v0.m_position.m_z + W2 * v1.m_position.m_z + W3 * v2.m_position.m_z;;
}

float Triangle::CheckAlpha(float W1, float W2, float W3)
{
	return W1 * v0.m_color.m_a + W2 * v1.m_color.m_a + W3 * v2.m_color.m_a;
}

Color Triangle::CheckColor(float W1, float W2, float W3)
{
	Color color;

	if (m_texture == nullptr)
	{
		color.m_r = (unsigned char)(W1 * v0.m_color.m_r + W2 * v1.m_color.m_r + W3 * v2.m_color.m_r);
		color.m_g = (unsigned char)(W1 * v0.m_color.m_g + W2 * v1.m_color.m_g + W3 * v2.m_color.m_g);
		color.m_b = (unsigned char)(W1 * v0.m_color.m_b + W2 * v1.m_color.m_b + W3 * v2.m_color.m_b);
	}
	else
	{
		float u = (W1 * v0.m_u + W2 * v1.m_u + W3 * v2.m_u) * m_texture->GetWidth() + 0.5f;
		float v = (W1 * v0.m_v + W2 * v1.m_v + W3 * v2.m_v) * m_texture->GetHeight();

		int uT = (int)(u - 0.5f);
		int vT = (int)(v - 0.5f);

		float ufrac = u - uT - 0.5f;
		float vfrac = v - vT - 0.5f;


		Color c00 = m_texture->GetPixelColor((vT * m_texture->GetWidth() + uT));
		Color c10 = m_texture->GetPixelColor((vT * m_texture->GetWidth() + (uT + 1)));
		Color c01 = m_texture->GetPixelColor(((vT + 1) * m_texture->GetWidth() + uT));
		Color c11 = m_texture->GetPixelColor(((vT + 1) * m_texture->GetWidth() + (uT + 1)));

		color.m_r = (unsigned char)(((c00.m_r * (1.f - ufrac)) * (1.f - vfrac)) +
			((c10.m_r * ufrac) * (1.f - vfrac)) +
			((c01.m_r * (1.f - ufrac)) * vfrac) +
			((c11.m_r * ufrac) * vfrac));

		color.m_g = (unsigned char)(((c00.m_g * (1.f - ufrac)) * (1.f - vfrac)) +
			((c10.m_g * ufrac) * (1.f - vfrac)) +
			((c01.m_g * (1.f - ufrac)) * vfrac) +
			((c11.m_g * ufrac) * vfrac));

		color.m_b = (unsigned char)(((c00.m_b * (1.f - ufrac)) * (1.f - vfrac)) +
			((c10.m_b * ufrac) * (1.f - vfrac)) +
			((c01.m_b * (1.f - ufrac)) * vfrac) +
			((c11.m_b * ufrac) * vfrac));

	}

	return color;
}

bool Triangle::isBackFace()
{
	Vec4 V1 = (v1.m_position - v0.m_position);
	Vec4 V2 = (v2.m_position - v0.m_position);

	float Nz = (V1.m_x * V2.m_y) - (V1.m_y * V2.m_x);

	return Nz >= 0;

}


