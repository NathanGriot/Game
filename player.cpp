#include "player.h"



player::player(sf::Texture* texture, sf::Vector2u imagecount, float switchtime,float speed,float jumpheight):
	Animation(texture,imagecount,switchtime)
{
	this->speed = speed;
	this->jumpheight = jumpheight;
	row = 0;
	facing = true;
	body.setSize(sf::Vector2f(100.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(100.0f, 100.0f);
	body.setTexture(texture); 
}


player::~player()
{
}

void player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void player::collision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		velocity.x = 0.0f;
	}
	if (direction.x > 0.0f)
	{
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		canjump = true;
		velocity.y = 0.0f;
	}
	if (direction.y > 0.0f)
	{
		velocity.y = 0.0f;
	}
}

sf::Vector2f player::getposition()
{
	return body.getPosition();
}

sf::Vector2f player::getcenterpos()
{
	sf::Vector2f pos = body.getPosition();
	sf::Vector2f size = body.getSize();
	centerpos = sf::Vector2f(pos.x + size.x / 2, pos.y + size.y /2);
	//cout << centerpos.x << " " << centerpos.y << endl; // test
	return centerpos;
}

bool player::getfacing()
{
	return facing;
}

void player::Update(float deltatime)
{
	//sf::Vector2f movement(0.0f, 0.0f);
	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		velocity.x -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		velocity.x += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)&& sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		velocity.x -= speed*2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		velocity.x += speed*2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canjump)
	{
		canjump = false;
		velocity.y = -sqrtf(2.0f *981.0f * jumpheight); //gravity math
	}

	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
	{
		movement.y -= speed * deltatime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		movement.y += speed * deltatime;
	}
	*/
	if(velocity.y != 0)
	{
		row = 2;
	}
	if (velocity.x == 0.0f && velocity.y == 0.0f )
	{
		row = 0;
	}
	if(velocity.x > 0.0f || velocity.x < 0.0f /*&& velocity.y ==0.0f*/)
	{
		row = 1;
		if (velocity.x > 0.0f)
			facing = true;
		else
			facing = false;
	}

	velocity.y += 981.0f * deltatime;
	Animation.Update(row, deltatime, facing);
	body.setTextureRect(Animation.textRect);
	body.move(velocity * deltatime);
	//cout << velocity.y << endl; //test 
}
