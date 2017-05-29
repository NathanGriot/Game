#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Menu.h"

const int screenWidth = 1920;
const int screenHeight = 1080;

int main(int argc, wchar_t* argv[])
{
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Game", sf::Style::Default);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(screenWidth, screenHeight));

	Menu menu(window);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						Game().handle(window, view);
						break;
					case 1:
						// TODO
						break;
					case 2:
						window.close();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}


		window.clear();
		menu.draw(window);
		window.display();
	}
}