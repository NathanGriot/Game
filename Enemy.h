#pragma once
#ifndef _ENEMY_H
#define _ENEMY_H

#include "Animation.h"
#include <stdio.h>
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Collision.h"
#include "Platform.h"
#include <stdlib.h>
#include <time.h>
#endif // !_ENEMY_H

using namespace std;
class Enemy
{
public:
	Enemy(sf::Texture*, sf::Vector2u, float, float, float);
	~Enemy();


	void update(float deltatime);
	void Draw(sf::RenderWindow& window);
	void collision(sf::Vector2f);

	bool isDead();
	bool isDecaying();
	void doDie();

	sf::Vector2f getposition();
	Collision getCollision() { return Collision(body); }
	sf::Vector2f centerpos;

private:

	Animation Animation;
	sf::RectangleShape body;
	unsigned int row;
	float speed;
	bool facing;
	int Rand;
	sf::Vector2f Velocity;
	bool canjump;
	float jumpheight;

	bool bDead;
	bool bDecaying;
	float decayingTick;
};
