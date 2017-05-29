#include "Collision.h"



Collision::Collision(sf::RectangleShape& body) :
	body(body)
{

}


Collision::~Collision()
{
}

bool Collision::checkCollision(Collision & other,sf::Vector2f& direction, float push)
{
	sf::Vector2f otherposition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f thisposition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherposition.x - thisposition.x;
	float deltaY = otherposition.y - thisposition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
	
	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				move(intersectX * (1.0f - push), 0.0f);
				other.move(-intersectX * push, 0.0f);

				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else
			{
				move(-intersectX * (1.0f - push), 0.0f);
				other.move(intersectX * push, 0.0f);

				direction.x = -1.0f;
				direction.y = 0.0f;
			}
			return true;
		}
		else
		{
			if (deltaY > 0.0f)
			{
				move(0.0f, intersectY * (1.0f - push));
				other.move(0.0f, -intersectY * push);

				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else
			{
				move(0.0f, -intersectY * (1.0f - push));
				other.move(0.0f, intersectY * push);

				direction.x = 0.0f;
				direction.y = -1.0f;
			}
			return true;
		}
	}
	return false;
}