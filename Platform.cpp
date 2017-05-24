#include "Platform.h"



Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}


Platform::~Platform()
{
}

void Platform::draw(sf::RenderWindow & window)
{
	window.draw(body);
}
