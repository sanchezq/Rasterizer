#pragma once

#include "Color.h"
#include <limits>
#include <vector>

class Texture
{
public:

	Texture(unsigned int x, unsigned int y);
	Texture(const char* img);

	~Texture();

	void SetPixelColor(unsigned int x, unsigned int y, const Color& c, float alpha, int i);
	void SetWireframePixelColor(unsigned int x, unsigned int y, const Color& c);
	void ResetPixelColor();

	Color GetPixelColor(unsigned int i);

	unsigned int GetWidth();
	unsigned int GetHeight();

	static Texture* GetInstance();
	Color* GetPixels();
	float* GetZBuffer();

private:

	unsigned int m_width;
	unsigned int m_height;

	Color* m_pixels = nullptr;

	float* m_zBuffer = nullptr;

	std::vector<int> m_PixelModif;

	static Texture* ms_instance;
};

