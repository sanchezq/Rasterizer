#include "pch.h"

#include "Suth-Hodg.h"

Vec3 LineIntersect(const Vec3& v1, const Vec3& v2, float x3, float y3, float x4, float y4)
{
	float x1 = v1.m_x,
		  y1 = v1.m_y,
	      x2 = v2.m_x,
		  y2 = v2.m_y;

	float num1 = (x1 * y2 - y1 * x2) * (x3 - x4) -
		(x1 - x2) * (x3 * y4 - y3 * x4);
	float den1 = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	float x = num1 / den1;

	float num2 = (x1 * y2 - y1 * x2) * (y3 - y4) -
		(y1 - y2) * (x3 * y4 - y3 * x4);
	float den2 = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	float y = num2 / den2;

	x1 = v1.m_z;
	x2 = v2.m_z;

	float z;
	if (x1 != x2)
	{
		float num3 = (x1 * y2 - y1 * x2) * (x1 - x2) -
			(x1 - x2) * (x1 * y - y * x2);
		float den3 = -(y1 - y2) * (x1 - x2);

		z = num3 / den3;
	}
	else
		z = v1.m_z;

	return Vec3(x, y, z);
}

Vec3 LineIntersect2(const Vec3& v1, const Vec3& v2, float x3, float y3, float x4, float y4)
{
	float x1 = v1.m_z,
		  y1 = v1.m_y,
		  x2 = v2.m_z,
		  y2 = v2.m_y;

	float num1 = (x1 * y2 - y1 * x2) * (x3 - x4) -
		(x1 - x2) * (x3 * y4 - y3 * x4);
	float den1 = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	float z = num1 / den1;

	float num2 = (x1 * y2 - y1 * x2) * (y3 - y4) -
		(y1 - y2) * (x3 * y4 - y3 * x4);
	float den2 = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	float y = num2 / den2;

	x1 = v1.m_x;
	x2 = v2.m_x;

	float x;
	if (x1 != x2)
	{
		float num3 = (x1 * y2 - y1 * x2) * (x1 - x2) -
			(x1 - x2) * (x1 * y - y * x2);
		float den3 = -(y1 - y2) * (x1 - x2);

		if (den3 == 0)
		{
			den3 = 1.f;
		}

		x = num3 / den3;
	}
	else
		x = v1.m_x;

	return Vec3(x, y, z);
}

std::vector<Vec3> PixClipLeft(std::vector<Vec3>& list, const Vertex& leftTopNearScreen, const Vertex& rightBotFarScreen)
{
	float min = leftTopNearScreen.m_position.m_x;
	auto it = list.begin();

	for (; it < list.end(); it++)
	{
		if (it->m_x < min)
		{
			it = list.begin();
			break;
		}
	}

	if (it > list.begin())
	{
		return list;
	}

	std::vector<Vec3> newList;

	float x1, x2,
		  x3 = leftTopNearScreen.m_position.m_x,
		  y3 = leftTopNearScreen.m_position.m_y,
		  x4 = leftTopNearScreen.m_position.m_x,
		  y4 = rightBotFarScreen.m_position.m_y;

	for (; it < list.end(); it++)
	{
		auto next = it;
		next++;

		if (next >= list.end())
			next = list.begin();

		x1 = it->m_x;
		x2 = next->m_x;

		if (x1 > min&& x2 > min)
			newList.push_back(*next);

		if (x1 > min&& x2 < min)
			newList.push_back(LineIntersect(*it, *next, x3, y3, x4, y4));

		if (x1 < min && x2 > min)
		{
			newList.push_back(LineIntersect(*it, *next, x3, y3, x4, y4));
			newList.push_back(*next);
		}
	}

	return newList;
}

std::vector<Vec3> PixClipBot(std::vector<Vec3>& list, const Vertex& leftTopNearScreen, const Vertex& rightBotFarScreen)
{
	float min = rightBotFarScreen.m_position.m_y;
	auto it = list.begin();

	for (; it < list.end(); it++)
	{
		if (it->m_y < min)
		{
			it = list.begin();
			break;
		}
	}

	if (it > list.begin())
	{
		return list;
	}

	std::vector<Vec3> newList;

	float y1, y2,
		  x3 = leftTopNearScreen.m_position.m_x,
		  y3 = rightBotFarScreen.m_position.m_y,
		  x4 = rightBotFarScreen.m_position.m_x,
		  y4 = rightBotFarScreen.m_position.m_y;

	for (; it < list.end(); it++)
	{
		auto next = it;
		next++;

		if (next >= list.end())
			next = list.begin();

		y1 = it->m_y;
		y2 = next->m_y;

		if (y1 > min&& y2 > min)
			newList.push_back(*next);

		if (y1 > min&& y2 < min)
			newList.push_back(LineIntersect(*it, *next, x3, y3, x4, y4));

		if (y1 < min && y2 > min)
		{
			newList.push_back(LineIntersect(*it, *next, x3, y3, x4, y4));
			newList.push_back(*next);
		}
	}

	return newList;
}

std::vector<Vec3> PixClipRight(std::vector<Vec3>& list, const Vertex& leftTopNearScreen, const Vertex& rightBotFarScreen)
{
	float max = rightBotFarScreen.m_position.m_x;
	auto it = list.begin();

	for (; it < list.end(); it++)
	{
		if (it->m_x > max)
		{
			it = list.begin();
			break;
		}
	}

	if (it > list.begin())
	{
		return list;
	}

	std::vector<Vec3> newList;

	float x1, x2,
		  x3 = rightBotFarScreen.m_position.m_x,
		  y3 = rightBotFarScreen.m_position.m_y,
		  x4 = rightBotFarScreen.m_position.m_x,
		  y4 = leftTopNearScreen.m_position.m_y;

	for (; it < list.end(); it++)
	{
		auto next = it;
		next++;

		if (next >= list.end())
			next = list.begin();

		x1 = it->m_x;
		x2 = next->m_x;

		if (x1 < max && x2 < max)
			newList.push_back(*next);

		if (x1 < max && x2 > max)
			newList.push_back(LineIntersect(*it, *next, x3, y3, x4, y4));

		if (x1 > max&& x2 < max)
		{
			newList.push_back(LineIntersect(*it, *next, x3, y3, x4, y4));
			newList.push_back(*next);
		}
	}

	return newList;
}

std::vector<Vec3> PixClipTop(std::vector<Vec3>& list, const Vertex& leftTopNearScreen, const Vertex& rightBotFarScreen)
{
	float max = leftTopNearScreen.m_position.m_y;
	auto it = list.begin();

	for (; it < list.end(); it++)
	{
		if (it->m_y > max)
		{
			it = list.begin();
			break;
		}
	}

	if (it > list.begin())
	{
		return list;
	}

	std::vector<Vec3> newList;

	float y1, y2,
		  x3 = rightBotFarScreen.m_position.m_x,
		  y3 = leftTopNearScreen.m_position.m_y,
		  x4 = leftTopNearScreen.m_position.m_x,
		  y4 = leftTopNearScreen.m_position.m_y;

	for (; it < list.end(); it++)
	{
		auto next = it;
		next++;

		if (next >= list.end())
			next = list.begin();

		y1 = it->m_y;
		y2 = next->m_y;

		if (y1 < max && y2 < max)
			newList.push_back(*next);

		if (y1 < max && y2 > max)
			newList.push_back(LineIntersect(*it, *next, x3, y3, x4, y4));

		if (y1 > max&& y2 < max)
		{
			newList.push_back(LineIntersect(*it, *next, x3, y3, x4, y4));
			newList.push_back(*next);
		}
	}

	return newList;
}

std::vector<Vec3> PixClipNear(std::vector<Vec3>& list, const Vertex& leftTopNearScreen, const Vertex& rightBotFarScreen)
{
	float min = leftTopNearScreen.m_position.m_z;
	auto it = list.begin();

	for (; it < list.end(); it++)
	{
		if (it->m_z < min)
		{
			it = list.begin();
			break;
		}
	}

	if (it > list.begin())
	{
		return list;
	}

	std::vector<Vec3> newList;

	float x1, x2,
		  x3 = leftTopNearScreen.m_position.m_z,
	      y3 = leftTopNearScreen.m_position.m_y,
		  x4 = leftTopNearScreen.m_position.m_z,
		  y4 = rightBotFarScreen.m_position.m_y;

	for (; it < list.end(); it++)
	{
		auto next = it;
		next++;

		if (next >= list.end())
			next = list.begin();

		x1 = it->m_z;
		x2 = next->m_z;

		if (x1 > min&& x2 > min)
			newList.push_back(*next);

		if (x1 > min&& x2 < min)
			newList.push_back(LineIntersect2(*it, *next, x3, y3, x4, y4));

		if (x1 < min && x2 > min)
		{
			newList.push_back(LineIntersect2(*it, *next, x3, y3, x4, y4));
			newList.push_back(*next);
		}
	}

	return newList;
}

std::vector<Vec3> PixClipFar(std::vector<Vec3>& list, const Vertex& leftTopNearScreen, const Vertex& rightBotFarScreen)
{
	float max = rightBotFarScreen.m_position.m_z;
	auto it = list.begin();

	for (; it < list.end(); it++)
	{
		if (it->m_z > max)
		{
			it = list.begin();
			break;
		}
	}

	if (it > list.begin())
	{
		return list;
	}

	std::vector<Vec3> newList;

	float x1, x2,
		  x3 = rightBotFarScreen.m_position.m_z,
		  y3 = rightBotFarScreen.m_position.m_y,
		  x4 = rightBotFarScreen.m_position.m_z,
		  y4 = leftTopNearScreen.m_position.m_y;

	for (; it < list.end(); it++)
	{
		auto next = it;
		next++;

		if (next >= list.end())
			next = list.begin();

		x1 = it->m_z;
		x2 = next->m_z;

		if (x1 < max && x2 < max)
			newList.push_back(*next);

		if (x1 < max && x2 > max)
			newList.push_back(LineIntersect2(*it, *next, x3, y3, x4, y4));

		if (x1 > max&& x2 < max)
		{
			newList.push_back(LineIntersect2(*it, *next, x3, y3, x4, y4));
			newList.push_back(*next);
		}
	}

	return newList;
}

std::vector<Vec3> PixelClipping(Vertex leftTopNearScreen, Vertex rightBotFarScreen, std::vector<Vec3> list)
{
	std::vector<Vec3> newList;

	leftTopNearScreen.m_position.m_y -= 1;
	rightBotFarScreen.m_position.m_x -= 1;

	newList = PixClipLeft(list, leftTopNearScreen, rightBotFarScreen);
	newList = PixClipBot(newList, leftTopNearScreen, rightBotFarScreen);
	newList = PixClipRight(newList, leftTopNearScreen, rightBotFarScreen);
	newList = PixClipTop(newList, leftTopNearScreen, rightBotFarScreen);
	newList = PixClipNear(newList, leftTopNearScreen, rightBotFarScreen);
	newList = PixClipFar(newList, leftTopNearScreen, rightBotFarScreen);

	return newList;
}