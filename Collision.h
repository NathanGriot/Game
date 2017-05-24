#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Collision
{
public:
	Collision(sf::RectangleShape& body);
	~Collision();

	void move(float dx, float dy) { body.move(dx, dy); }
	bool checkcollision(Collision & other,sf::Vector2f&, float push);

	sf::Vector2f GetPosition() { return body.getPosition(); };
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; };
private:
	sf::RectangleShape& body;
};

