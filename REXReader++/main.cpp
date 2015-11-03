#if defined(_WIN32)
#include <windows.h>

extern int main();
INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	return main();
}

#define WIN32_LEAN_AND_MEAN

#endif

#include <iostream>
#include <SFML/Graphics.hpp>
#include "XPText.hpp"

int main()
{
	SetConsoleTitle(TEXT("RexReader++"));

	sf::RenderWindow window(sf::VideoMode(640, 720), "RexReader++ Test");

	sf::Font font;
	if (!font.loadFromFile("cp437-8x8.ttf"))
		return EXIT_FAILURE;
	sf::Text text("REXPaint Reader and SFML XPText - Gamepopper 2015", font, 12);
	text.setPosition(sf::Vector2f(320.0f - text.getLocalBounds().width / 2, 0.0f));

	sf::XPText xpText("test.xp", font, 10);
	xpText.setPosition(320.0f - (xpText.getLocalBounds().width / 2), 360.0f - (xpText.getLocalBounds().height / 2));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(text);
		window.draw(xpText);
		window.display();
	}
	return EXIT_SUCCESS;
}