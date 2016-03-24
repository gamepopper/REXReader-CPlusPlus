#include "RexReader.h"
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
	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 2; j++)
		{
			layerSizes[i][j] = -1;
		}
	}

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

int RexReader::GetLayerWidth(int layer)
{
	CheckDisposed();

	if (layer < 0 || layer >= GetLayerCount())
	{
		throw ("Layer out of bounds");
	}

	if (layerSizes[layer][0] > 0)
	{
		return layerSizes[layer][0];
	}

	int offset = (layerCountOffset * 8 + 32 + layer * 64)/8;
	layerSizes[layer][0] = GetInt(filestream, offset);

	return layerSizes[layer][0];
}

int RexReader::GetLayerHeight(int layer)
{
	CheckDisposed();

	if (layer < 0 || layer > GetLayerCount())
	{
		throw ("Layer out of bounds");
	}

	if (layerSizes[layer][1] > 0)
	{
		return layerSizes[layer][1];
	}

	int offset = (layerCountOffset * 8 + 32 + 32 + layer * 64)/8;
	layerSizes[layer][1] = GetInt(filestream, offset);

	return layerSizes[layer][1];
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
		width = GetLayerWidth(0);
		height = GetLayerHeight(0);
	}
	catch (int e)
	{
		Dispose();
		throw("Bad .xp file " + e);
	}

	auto map = new RexTileMap(width, height, layers);
	int offset = 16;
	gzseek(filestream, offset, SEEK_SET);

	for (unsigned int layer = 0; layer < layers; layer++)
	{
		for (unsigned int x = 0; x < width; x++)
			for (unsigned int y = 0; y < height; y++)
			{
				RexTile* tile = &map->Layers[layer]->Tiles[x + (y * width)];
				tile->CharacterCode = GetInt(filestream);
				tile->ForegroundRed = GetChar(filestream);
				tile->ForegroundGreen = GetChar(filestream);
				tile->ForegroundBlue = GetChar(filestream);
				tile->BackgroundRed = GetChar(filestream);
				tile->BackgroundGreen = GetChar(filestream);
				tile->BackgroundBlue = GetChar(filestream);
			}
		offset = 16 + ((10 * width * height) + 8) * (layer + 1);
		gzseek(filestream, offset, SEEK_SET);
	}

	return map;
}