#pragma once
#ifndef _PLATFORM_H
#define _PLATFORM_H

#include <SFML\Graphics.hpp>
#include "Collision.h"
#endif // !_PLATFORM_H

class Platform
{
public:
	Platform(sf::Texture* texture,sf::Vector2f size,sf::Vector2f position);
	~Platform();
	void draw(sf::RenderWindow& window);
	Collision getCollision() { return Collision(body); }

private:
	sf::RectangleShape body;
};

