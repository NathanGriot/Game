#pragma once
#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include <SFML\Graphics.hpp>
#include "Collision.h"
#endif // !_PROJECTILE_H


class Projectile
{
public:
	Projectile( int speed, sf::Vector2f position);
	~Projectile();
	void draw(sf::RenderWindow & window);
	void update(float);
	void setpose(sf::Vector2f,bool);
	Collision getCollision() { return Collision(body); }
private:
	sf::RectangleShape body;
	int speed;
	bool face;
	sf::Vector2f movement;
};

