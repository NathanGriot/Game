#include "Projectile.h"

Projectile::Projectile(int speed, sf::Vector2f position)
{
	this->speed = speed;
	this->face = true;
	body.setSize(sf::Vector2f(25.0f, 5.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position.x, position.y);
	body.setFillColor(sf::Color::Red);
}

Projectile::~Projectile()
{
}

void Projectile::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Projectile::update(float deltatime)
{
	//sf::Vector2f movement(0.0f, 0.0f);
	//body.setPosition(pose.x, pose.y);
	movement.x = 0.0f;
	movement.y = 0.0f;

	if (face == false)
	{
		movement.x -= speed;
	}
	if (face == true)
	{
		movement.x += speed;
	}

	body.move(movement * deltatime);
	//cout << velocity.y << endl; //test 
}

void Projectile::setpose(sf::Vector2f pose, bool facing)
{
	body.setPosition(pose);
	face = facing;
}
