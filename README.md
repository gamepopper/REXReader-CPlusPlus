The following is a set of classes that make use of GridSageGames' [REXPaint ASCII Art Tool](http://rexpaint.blogspot.com/).

## REXReader-C++
A lightweight C++ class for reading REXPaint files into an easy to use format using zlib, based on [Baconsoap's RexReader](https://github.com/BaconSoap/RexReader).

## XPText
An entity for SFML 2.0 that renders REXPaint images using RexReader-C++.

![Left: REXPaint-R9 - Right: SFML 2.3.2 with XPText](http://i.imgur.com/sVwwurG.png)

## Usage
The most basic usage for the RexReader++ is as follows:
```
RexReader xpReader;
xpReader.LoadFile("example.xp");
RexTileMap* tilemap = xpReader.GetTileMap();
```

As like Baconsoap's library, the tilemap structure is as follows. The amount of RexTileLayers is 4, however it's advised to use GetLayerCount() for the exact amount of layers in an image, (any non-existant layers are NULL by default). The amount of RexTiles in a RexTileLayer is (LayerWidth*LayerHeight), you can access the layer width and height by calling GetLayerWidth(layer) and GetLayerHeight(layer). It's best to access a specific tile by using: x + (y * width).
```
| RexTileMap
| | RexTileLayer[] Layers
| | | RexTile[] Tiles
| | | | int CharacterCode
| | | | unsigned char ForegroundRed
| | | | unsigned char ForegroundGreen
| | | | unsigned char ForegroundBlue
| | | | unsigned char BackgroundRed
| | | | unsigned char BackgroundGreen
| | | | unsigned char BackgroundBlue
```

XPText aims to have similar syntax and functionality as SFML's Text class, as such the usage is very similar.

```
\\Initialising
sf::Font font;
font.loadFromFile("cp437-8x8.ttf");

sf::Text text("REXPaint Reader and SFML XPText - Gamepopper 2015", font, 12);
sf::XPText xpText("test.xp", font, 10);

\\Transforming
text.setPosition(20.0f, 40.0f));
xpText.setPosition(20.0f, 40.0f));

\\Changing Tint
text.setColor(sf::Color::Red);
xpText.setColor(sf::Color::Red);

\\Render
window.draw(text);
window.draw(xpText);
```

## Licensing
> The MIT License (MIT)

> Copyright (c) 2015 Tim Stoddard

> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
