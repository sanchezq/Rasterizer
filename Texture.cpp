#include "pch.h"
#include "Texture.h"

#include "Color.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#include <iostream>

Texture* Texture::ms_instance = nullptr;

Texture::Texture(unsigned int x, unsigned int y) :
	m_width(x), m_height(y)
{
	ms_instance = this;
	m_pixels = new Color[x * y];
	m_zBuffer = new float[x * y];

	for (int i = 0; i < (int)(x * y); i++)
	{
		m_zBuffer[i] = std::numeric_limits<float>::lowest();
	}
}

Texture::Texture(const char* img)
{
	int width, height, comp;

	stbi_set_flip_vertically_on_load(true);

	stbi_uc* texture = stbi_load(img, &width, &height, &comp, 0);

	m_width = width;
	m_height = height;

	m_pixels = new Color[m_width * m_height];

	for (int i = 0; i < (int)(m_width * m_height * comp); i++)
	{
		if (i % comp == 0)
		{
			m_pixels[int(i / comp)].m_r = texture[i];
		}
		else if (i % comp == 1)
		{
			m_pixels[int(i / comp)].m_g = texture[i];
		}
		else if (i % comp == 2)
		{
			m_pixels[int(i / comp)].m_b = texture[i];
		}
		else
		{
			m_pixels[int(i / comp)].m_a = texture[i];
		}
	}

	stbi_image_free(texture);
}


Texture::~Texture()
{
	delete[] m_pixels;
}

void Texture::SetPixelColor(unsigned int x, unsigned int y, const Color& c, float alpha, int i)
{

	if (alpha / 255 != 1)
	{
		Color color;
		color.m_r = (unsigned char)(((c.m_r * (alpha / 255)) + ((GetPixelColor(i).m_r * 1) * (1 - (alpha / 255)))) / ((alpha / 255) + (1 * (1 - (alpha / 255)))));
		color.m_g = (unsigned char)(((c.m_g * (alpha / 255)) + ((GetPixelColor(i).m_g * 1) * (1 - (alpha / 255)))) / ((alpha / 255) + (1 * (1 - (alpha / 255)))));
		color.m_b = (unsigned char)(((c.m_b * (alpha / 255)) + ((GetPixelColor(i).m_b * 1) * (1 - (alpha / 255)))) / ((alpha / 255) + (1 * (1 - (alpha / 255)))));
		m_pixels[i] = color;
	}
	else
	{
		m_pixels[i] = c;
	}
	m_PixelModif.push_back(i);
}

void Texture::SetWireframePixelColor(unsigned int x, unsigned int y, const Color& c)
{
	if (y < m_height && x < m_width)
	{
		int i = y * m_width + x;
		m_pixels[i] = c;
		m_PixelModif.push_back(i);
	}
}

void Texture::ResetPixelColor()
{
	int total = m_width * m_height;

	for (auto current : m_PixelModif)
	{
		m_zBuffer[current] = (float)std::numeric_limits<int>::lowest();
		m_pixels[current] = { 0, 0, 0 };
	}
	m_PixelModif.clear();
}

Color Texture::GetPixelColor(unsigned int i)
{
	return m_pixels[i];
}

unsigned int Texture::GetWidth()
{
	return m_width;
}

unsigned int Texture::GetHeight()
{
	return m_height;
}

Texture* Texture::GetInstance()
{
	return ms_instance;
}

Color* Texture::GetPixels()
{
	return m_pixels;
}

float* Texture::GetZBuffer()
{
	return m_zBuffer;
}
