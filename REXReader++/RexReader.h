#pragma once
#include "RexTile.h"
#include <iostream>
#include "zlib.h"
#include "zconf.h"

class RexReader
{
private:
	unsigned int layerCountOffset;

	gzFile filestream;

	bool disposed = false;
	int layerCount = -1;
	int layerSizes[4][2];

	int GetInt(gzFile& in, int position = -1);
	unsigned char GetChar(gzFile& in, int position = -1);
	void CheckDisposed();

public:
	RexReader() = default;
	~RexReader() = default;

	bool LoadFile(std::string filename);
	void Dispose();

	int GetLayerCount();
	int GetLayerWidth(int layer);
	int GetLayerHeight(int layer);

	RexTileMap* GetTileMap();
};