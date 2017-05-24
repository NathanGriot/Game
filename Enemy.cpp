#include "Enemy.h"




Enemy::Enemy(sf::Texture* texture, sf::Vector2u imagecount, float switchtime, float speed, float jumpheight) :Animation(texture, imagecount, switchtime)
{
	this->speed = speed;
	this->jumpheight = jumpheight;
	row = 0;
	facing = true;
	body.setSize(sf::Vector2f(60.0f, 60.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(100.0f, 100.0f);
	body.setTexture(texture);
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltatime)
{
	Velocity.x = 0.0f;
	srand(time(NULL));
	Rand = rand() % 2 + 1;
	if (Rand == 1)
	{
		Velocity.x -= speed;
	}
	if (Rand == 2)
	{
		Velocity.x += speed;
	}

	if (Velocity.y != 0)
	{
		row = 0;
	}
	if (Velocity.x == 0.0f && Velocity.y == 0.0f)
	{
		row = 0;
	}
	if (Velocity.x > 0.0f || Velocity.x < 0.0f /*&& velocity.y ==0.0f*/)
	{
		row = 0;
		if (Velocity.x > 0.0f)
			facing = true;
		else
			facing = false;
	}
	//Velocity.y = -sqrtf(2.0f *981.0f * jumpheight); //gravity math
	Velocity.y += 981.0f * deltatime;
	Animation.Update(row, deltatime, facing);
	body.setTextureRect(Animation.textRect);
	body.move(Velocity * deltatime);

	//cout << Velocity.y << endl;
}

void Enemy::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

void Enemy::collision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		Velocity.x = 0.0f;
	}
	if (direction.x > 0.0f)
	{
		Velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		canjump = true;
		Velocity.y = 0.0f;
	}
	if (direction.y > 0.0f)
	{
		Velocity.y = 0.0f;
	}
}

sf::Vector2f Enemy::getposition()
{
	return sf::Vector2f();
}
