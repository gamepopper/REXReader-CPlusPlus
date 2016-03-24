#pragma once
#include <iostream>

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
	RexTile* Tiles;
	RexTileLayer() = default;
	RexTileLayer(int width, int height)
	{
		Tiles = new RexTile[width * height];
	}
	~RexTileLayer()
	{
		delete[] Tiles;
		Tiles = NULL;
	}
};

class RexTileMap
{
private:
	unsigned int width;
	unsigned int height;
	unsigned int layerCount;

public:
	RexTileLayer* Layers[4];

	RexTileMap(unsigned int width, unsigned int height, unsigned int layers)
	{
		this->width = width;
		this->height = height;
		this->layerCount = layers;
		for (unsigned int i = 0; i < layerCount; i++)
		{
			this->Layers[i] = new RexTileLayer(width, height);
		}
	}
	~RexTileMap()
	{
		for (unsigned int i = 0; i < layerCount; i++)
		{
			delete(Layers[i]);
		}
	}
};