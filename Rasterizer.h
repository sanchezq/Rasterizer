#pragma once

#include "Scene.h"
#include "Texture.h"
#include "Camera.h"

class Rasterizer
{
public:

	Rasterizer();
	void RendererScene(Scene* pScene, Texture* pTarget, const Mat4& projectionMatrix, const Mat4& inverseCameraMatrix, bool wireframe, bool backface, Camera camera);
	static Rasterizer* GetInstance();
	static Mat4 CreatePerspectiveProjectionMatrix(int width, int height, float near, float far, float fov);

private:

	static Rasterizer* ms_instance;
};
