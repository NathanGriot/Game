#include "Background.h"

Background::Background(sf::Texture* background, sf::Vector2f size, sf::Vector2f position)
	: Background(background, size, position, size / 2.0f)
{
}

Background::Background(sf::Texture* background, sf::Vector2f size, sf::Vector2f position, sf::Vector2f origin)
{
	body.setSize(size);
	body.setOrigin(origin);
	body.setTexture(background);
	body.setPosition(position);
}

void Background::draw(sf::RenderWindow& window)
{
	window.draw(body);
}


Background::~Background()
{
}
