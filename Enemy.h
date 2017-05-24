#pragma once
#include "animation.h"
#include <stdio.h>
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Collision.h"
#include "Platform.h"
#include <stdlib.h>
#include <time.h>

using namespace std;
class Enemy
{
public:
	Enemy(sf::Texture*, sf::Vector2u, float, float, float);
	~Enemy();


	void Update(float deltatime);
	void Draw(sf::RenderWindow& window);
	void collision(sf::Vector2f);

	sf::Vector2f getposition();
	Collision GetCollision() { return Collision(body); }
	sf::Vector2f centerpos;

private:

	animation Animation;
	sf::RectangleShape body;
	unsigned int row;
	float speed;
	bool facing;
	int Rand;
	sf::Vector2f Velocity;
	bool canjump;
	float jumpheight;
};
