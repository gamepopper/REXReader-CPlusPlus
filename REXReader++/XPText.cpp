#include "XPText.hpp"

#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include "RexReader.h"
#include <cmath>

namespace sf
{
	XPText::XPText()
	{
		filename = "";
		font = NULL;
		characterSize = 30;
		tint = Color::White;
		vertices = sf::VertexArray(Triangles);
		bounds = sf::FloatRect();
		geometryNeedsUpdate = false;
	}

	XPText::XPText(std::string filename, const Font& font, unsigned int characterSize)
	{
		this->filename = filename;
		this->font = &font;
		this->characterSize = characterSize;
		tint = Color::White;
		vertices = sf::VertexArray(Triangles);
		bounds = sf::FloatRect();
		geometryNeedsUpdate = true;
	}

	XPText::~XPText()
	{

	}

	void XPText::setFileName(std::string filename)
	{
		if (this->filename != filename)
		{
			this->filename = filename;
			geometryNeedsUpdate = true;
		}
	}

	void XPText::setFont(const Font& font)
	{
		if (this->font != &font)
		{
			this->font = &font;
			geometryNeedsUpdate = true;
		}
	}

	void XPText::setCharacterSize(unsigned int size)
	{
		if (characterSize != size)
		{
			characterSize = size;
			geometryNeedsUpdate = true;
		}
	}

	void XPText::setColor(const Color& color)
	{
		if (tint != color)
		{
			tint = color;
			geometryNeedsUpdate = true;
		}
	}

	const std::string& XPText::getFileName()
	{
		return filename;
	}

	const Font* XPText::getFont() const
	{
		return font;
	}

	FloatRect XPText::getLocalBounds() const
	{
		updateGeometry();

		return bounds;
	}

	FloatRect XPText::getGlobalBounds() const
	{
		return getTransform().transformRect(getLocalBounds());
	}

	void XPText::draw(RenderTarget& target, RenderStates states) const
	{
		if (font)
		{
			updateGeometry();

			states.transform *= getTransform();
			states.texture = &font->getTexture(characterSize);
			target.draw(vertices, states);
		}
	}

	void XPText::updateGeometry() const
	{
		if (!geometryNeedsUpdate)
			return;

		geometryNeedsUpdate = false;

		RexReader xpReader;

		if (!xpReader.LoadFile(filename))
			return;

		int layers = xpReader.GetLayerCount();

		if (layers == 0)
			return;

		int width = xpReader.GetLayerWidth(0);
		int height = xpReader.GetLayerHeight(0);

		RexTileMap* tilemap = xpReader.GetTileMap();

		sf::Glyph bgGlyph = font->getGlyph(219, characterSize, false);

		//Get the natural width and height of each character in the grid.
		float hspace = bgGlyph.advance;
		float vspace = font->getLineSpacing(characterSize);

		//SFML glyphs have an offset for line spacing purposes. These offsets should counteract them.
		float topOffset = bgGlyph.bounds.top;
		float bottomOffset = vspace + topOffset;

		for (int layer = 0; layer < layers; layer++)
			for (int x = 0; x < width; x++)
				for (int y = 0; y < height; y++)
				{
					RexTile& tile = tilemap->Layers[layer]->Tiles[x + (y * width)];
					
					if (tile.BackgroundRed == 255 &&
						tile.BackgroundGreen == 0 &&
						tile.BackgroundBlue == 255)
					{
						continue;
					}

					sf::Glyph glyph = font->getGlyph(tile.CharacterCode, characterSize, false);

					float left = glyph.bounds.left;
					float top = glyph.bounds.top;
					float right = glyph.bounds.left + glyph.bounds.width;
					float bottom = glyph.bounds.top + glyph.bounds.height;

					float u1 = static_cast<float>(glyph.textureRect.left);
					float v1 = static_cast<float>(glyph.textureRect.top);
					float u2 = static_cast<float>(glyph.textureRect.left + glyph.textureRect.width);
					float v2 = static_cast<float>(glyph.textureRect.top + glyph.textureRect.height);

					sf::Color foreground = sf::Color(tile.ForegroundRed, tile.ForegroundGreen, tile.ForegroundBlue, 255) * tint;
					sf::Color background = sf::Color(tile.BackgroundRed, tile.BackgroundGreen, tile.BackgroundBlue, 255) * tint;


					vertices.append(sf::Vertex(Vector2f((x*hspace) + 0,			(y*vspace) + topOffset),	background));
					vertices.append(sf::Vertex(Vector2f((x*hspace) + hspace,	(y*vspace) + topOffset),	background));
					vertices.append(sf::Vertex(Vector2f((x*hspace) + 0,			(y*vspace) + bottomOffset),	background));
					vertices.append(sf::Vertex(Vector2f((x*hspace) + 0,			(y*vspace) + bottomOffset),	background));
					vertices.append(sf::Vertex(Vector2f((x*hspace) + hspace,	(y*vspace) + topOffset),	background));
					vertices.append(sf::Vertex(Vector2f((x*hspace) + hspace,	(y*vspace) + bottomOffset),	background));

					vertices.append(sf::Vertex(Vector2f((x*hspace) + left,		(y*vspace) + top),		foreground, Vector2f(u1, v1)));
					vertices.append(sf::Vertex(Vector2f((x*hspace) + right,		(y*vspace) + top),		foreground, Vector2f(u2, v1)));
					vertices.append(sf::Vertex(Vector2f((x*hspace) + left,		(y*vspace) + bottom),	foreground, Vector2f(u1, v2)));
					vertices.append(sf::Vertex(Vector2f((x*hspace) + left,		(y*vspace) + bottom),	foreground, Vector2f(u1, v2)));
					vertices.append(sf::Vertex(Vector2f((x*hspace) + right,		(y*vspace) + top),		foreground, Vector2f(u2, v1)));
					vertices.append(sf::Vertex(Vector2f((x*hspace) + right,		(y*vspace) + bottom),	foreground, Vector2f(u2, v2)));
				}

		bounds.left = 0;
		bounds.top = topOffset;
		bounds.width = hspace * width;
		bounds.height = vspace * height;
	}
}