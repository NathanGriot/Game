#pragma once
#ifndef _COLLISION_H
#define _COLLISION_H

#include <SFML\Graphics.hpp>
#endif // !_COLLISION_H

class Collision
{
public:
	Collision(sf::RectangleShape& body);
	~Collision();

	void move(float dx, float dy) { body.move(dx, dy); }
	bool checkCollision(Collision & other,sf::Vector2f&, float push);

	sf::Vector2f GetPosition() { return body.getPosition(); };
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; };
private:
	sf::RectangleShape& body;
};

