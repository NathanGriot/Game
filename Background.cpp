#include "Background.h"



Background::Background(sf::Texture* background, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
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
