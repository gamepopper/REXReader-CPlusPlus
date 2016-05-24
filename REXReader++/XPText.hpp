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

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/String.hpp>
#include <string>

namespace sf
{
	class XPText : public Drawable, public Transformable
	{
	public:
		XPText();
		XPText(std::string filename, const Font& font, unsigned int characterSize = 30);
		~XPText();

		void setFileName(std::string filename);
		void setFont(const Font& font);
		void setCharacterSize(unsigned int size);
		void setColor(const Color& color);

		const std::string& getFileName();
		const Font* getFont() const;

		FloatRect getLocalBounds() const;
		FloatRect getGlobalBounds() const;

	private:
		virtual void draw(RenderTarget& target, RenderStates states) const;

		void updateGeometry() const;

		std::string				filename;
		const Font*				font;
		Color					tint;
		unsigned int			characterSize;
		mutable VertexArray		vertices;
		mutable FloatRect		bounds;
		mutable bool			geometryNeedsUpdate;
	};
}

