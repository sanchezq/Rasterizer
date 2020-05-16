#pragma once

#include "Vertex.h"
#include <vector>
#include <iostream>


Vec3 LineIntersect(const Vec3& v1, const Vec3& v2, float x3, float y3, float x4, float y4);
std::vector<Vec3> PixClipLeft(std::vector<Vec3>& list, const Vertex& leftTopNearScreen, const Vertex& rightBotFarScreen);
std::vector<Vec3> PixClipBot(std::vector<Vec3>& list, const Vertex& leftTopNearScreen, const Vertex& rightBotFarScreen);
std::vector<Vec3> PixClipRight(std::vector<Vec3>& list, const Vertex& leftTopNearScreen, const Vertex& rightBotFarScreen);
std::vector<Vec3> PixClipTop(std::vector<Vec3>& list, const Vertex& leftTopNearScreen, const Vertex& rightBotFarScreen);

Vec3 LineIntersect2(const Vec3& v1, const Vec3& v2, float x3, float y3, float x4, float y4);
std::vector<Vec3> PixClipFar(std::vector<Vec3>& list, const Vertex& leftTopNearScreen, const Vertex& rightBotFarScreen);
std::vector<Vec3> PixClipNear(std::vector<Vec3>& list, const Vertex& leftTopNearScreen, const Vertex& rightBotFarScreen);

std::vector<Vec3> PixelClipping(Vertex leftTopNearScreen, Vertex rightBotFarScreen, std::vector<Vec3> list);
