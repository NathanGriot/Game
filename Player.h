#pragma once
#ifndef _PLAYER_H
#define _PLAYER_H

#include "Animation.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Collision.h"
#include "Platform.h"
#endif // !_PLAYER_H

using namespace std;
class Player
{
public:
	Player(sf::Texture*, sf::Vector2u, float, float,float);
	~Player();


	void update(float deltatime);
	void Draw(sf::RenderWindow& window);
	void collision(sf::Vector2f);

	sf::Vector2f getPosition(); 
	sf::Vector2f getCenterPos();
	bool getFacing();
	Collision GetCollision() { return Collision(body); }
	sf::Vector2f centerpos;

private:
	Animation Animation;
	sf::RectangleShape body;
	unsigned int row;
	float speed;
	bool facing;

	sf::Vector2f velocity;
	bool canjump;
	float jumpheight;
};

