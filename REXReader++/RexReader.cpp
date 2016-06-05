#include "RexReader.h"
#include <iostream>
using namespace std;

int RexReader::GetInt(gzFile& in, int position)
{
	int value = 0;
	Byte buffer[4];

	if (position >= 0)
	{
		if (gzseek(in, position, SEEK_SET) == -1)
			return 0;
	}

	gzread(in, buffer, 4);

	value = (value << 8) + buffer[3];
	value = (value << 8) + buffer[2];
	value = (value << 8) + buffer[1];
	value = (value << 8) + buffer[0];

	return value;
}

unsigned char RexReader::GetChar(gzFile& in, int position)
{
	unsigned char value = 0;
	Byte buffer[1];

	if (position >= 0)
	{
		if (gzseek(in, position, SEEK_SET) == -1)
			return 0;
	}

	gzread(in, buffer, 1);

	value = buffer[0];

	return value;
}

void RexReader::CheckDisposed()
{
	if (disposed)
	{
		throw("RexReader is disposed");
	}
}

bool RexReader::LoadFile(std::string filename)
{
	filestream = gzopen(filename.c_str(), "rb");
	if (filestream == NULL) {
		std::cout << "Error: Failed to gzopen " << filename.c_str() << std::endl;
		return false;
	}

	int version = GetInt(filestream, 0);
	if (version < 0)
	{
		layerCountOffset = 4;
	}

	layerCount = -1;
	for (unsigned int i = 0; i < 2; i++)
	{
		layerSizes[i] = -1;
	}

	disposed = false;

	return true;
}

void RexReader::Dispose()
{
	gzclose(filestream);
	disposed = true;
}

int RexReader::GetLayerCount()
{
	CheckDisposed();

	if (layerCount > 0)
	{
		return layerCount;
	}

	layerCount = GetInt(filestream, layerCountOffset);
	return layerCount;
}

int RexReader::GetLayerWidth()
{
	CheckDisposed();

	if (layerSizes[0] > 0)
	{
		return layerSizes[0];
	}

	int offset = (layerCountOffset * 8 + 32)/8;
	layerSizes[0] = GetInt(filestream, offset);

	return layerSizes[0];
}

int RexReader::GetLayerHeight()
{
	CheckDisposed();

	if (layerSizes[1] > 0)
	{
		return layerSizes[1];
	}

	int offset = (layerCountOffset * 8 + 32 + 32)/8;
	layerSizes[1] = GetInt(filestream, offset);

	return layerSizes[1];
}

RexTileMap* RexReader::GetTileMap()
{
	CheckDisposed();
	unsigned int layers;
	unsigned int width;
	unsigned int height;

	try
	{
		layers = GetLayerCount();
		width = GetLayerWidth();
		height = GetLayerHeight();
	}
	catch (int e)
	{
		Dispose();
		throw("Bad .xp file: %d", e);
	}

	auto map = new RexTileMap(width, height, layers);
	int offset = 16;
	gzseek(filestream, offset, SEEK_SET);

	for (unsigned int layer = 0; layer < layers; layer++)
	{
		for (unsigned int x = 0; x < width; x++)
			for (unsigned int y = 0; y < height; y++)
			{
				RexTile* tile = new RexTile();
				gzread(filestream, tile, 10);
				map->Layers[layer]->Tiles[x + (y * width)] = std::unique_ptr<RexTile>(tile);
			}
		offset = 16 + ((10 * width * height) + 8) * (layer + 1);
		gzseek(filestream, offset, SEEK_SET);
	}

	return map;
}