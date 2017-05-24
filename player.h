#pragma once
#include "animation.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Collision.h"
#include "Platform.h"

using namespace std;
class player
{
public:
	player(sf::Texture*, sf::Vector2u, float, float,float);
	~player();


	void Update(float deltatime);
	void Draw(sf::RenderWindow& window);
	void collision(sf::Vector2f);

	sf::Vector2f getposition(); 
	sf::Vector2f getcenterpos();
	bool getfacing();
	Collision GetCollision() { return Collision(body); }
	sf::Vector2f centerpos;

private:
	animation Animation;
	sf::RectangleShape body;
	unsigned int row;
	float speed;
	bool facing;

	sf::Vector2f velocity;
	bool canjump;
	float jumpheight;
};

