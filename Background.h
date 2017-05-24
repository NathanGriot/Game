#pragma once
#include <SFML\Graphics.hpp>
class Background
{
public:
	Background(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	void draw(sf::RenderWindow&);
	~Background();
private:
	sf::RectangleShape body;
};

