#pragma once
class Color
{
public:

	Color() = default;
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

	unsigned char m_r = 0;
	unsigned char m_g = 0;
	unsigned char m_b = 0;
	unsigned char m_a = 255;
};

