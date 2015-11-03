#pragma once

#include <SFML/Graphics/Export.hpp>
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Transformable.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\Graphics\VertexArray.hpp>
#include <SFML\System\String.hpp>
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

