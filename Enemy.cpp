#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imagecount, float switchtime, float speed, float jumpheight) :Animation(texture, imagecount, switchtime)
{
	this->speed = speed;
	this->jumpheight = jumpheight;
	row = 0;
	facing = true;
	body.setSize(sf::Vector2f(60.0f, 60.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(600.0f, 400.0f);
	body.setTexture(texture);

	bDead = false;
	bDecaying = false;
}

Enemy::~Enemy()
{
}

void Enemy::update(float deltatime)
{
	if (isDead())
		return;

	if (isDecaying())
	{
		decayingTick -= deltatime;
		if (decayingTick <= 0.0f)
		{
			bDead = true;
			bDecaying = false;
		}
		return;
	}

	Velocity.x = 0.0f;
	srand((unsigned int)time(NULL));
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
	if (isDecaying())
		body.setFillColor(sf::Color(255, 255, 255, 255 * decayingTick));
	window.draw(body);
}

void Enemy::collision(sf::Vector2f direction)
{
	if (isDecaying() || isDead())
		return;

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

void Enemy::doDie()
{
	bDecaying = true;
	decayingTick = 1.0f;
}

bool Enemy::isDead()
{
	return bDead;
}

bool Enemy::isDecaying()
{
	return bDecaying;
}