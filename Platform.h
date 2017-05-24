#pragma once
#include <SFML\Graphics.hpp>
#include "Collision.h"
class Platform
{
public:
	Platform(sf::Texture* texture,sf::Vector2f size,sf::Vector2f position);
	~Platform();
	void draw(sf::RenderWindow& window);
	Collision getcollision() { return Collision(body); }

private:
	sf::RectangleShape body;
};

