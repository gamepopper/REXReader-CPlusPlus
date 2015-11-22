#pragma once
#include <iostream>
#include <vector>
#include <memory>

struct RexTile
{
	unsigned int CharacterCode;
	unsigned int BackgroundRed;
	unsigned int BackgroundGreen;
	unsigned int BackgroundBlue;
	unsigned int ForegroundRed;
	unsigned int ForegroundGreen;
	unsigned int ForegroundBlue;
};

class RexTileLayer
{
public:
	std::vector<std::unique_ptr<RexTile>> Tiles;
	RexTileLayer() = default;
	RexTileLayer(int width, int height)
	{
		Tiles = std::vector<std::unique_ptr<RexTile>>(width * height);
	}
	~RexTileLayer()
	{
		Tiles.clear();
	}
};

class RexTileMap
{
private:
	unsigned int width;
	unsigned int height;
	unsigned int layerCount;

public:
	std::vector<std::unique_ptr<RexTileLayer>> Layers;

	RexTileMap(unsigned int width, unsigned int height, unsigned int layers)
	{
		this->width = width;
		this->height = height;
		this->layerCount = layers;

		Layers = std::vector<std::unique_ptr<RexTileLayer>>(this->layerCount);
		for (unsigned int i = 0; i < layerCount; i++)
		{
			this->Layers[i] = std::make_unique<RexTileLayer>(width, height);
		}
	}
	~RexTileMap() = default;
};