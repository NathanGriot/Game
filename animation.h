#pragma once
#include <SFML\Graphics.hpp>

class animation
{
public:
	animation(sf::Texture*, sf::Vector2u,float);
	~animation();
	void Update(int, float, bool);

	sf::IntRect textRect;

private:
	sf::Vector2u imagecount;
	sf::Vector2u currentimage;

	float totaltime;
	float switchtime;

};

