#pragma once

/*
The MIT License (MIT)
Copyright (c) 2015 Tim Stoddard
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files 
(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, 
publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "RexTile.h"
#include "zlib.h"

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