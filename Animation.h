#pragma once
#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <SFML\Graphics.hpp>
#endif // !_ANIMATION_H

class Animation
{
public:
	Animation(sf::Texture*, sf::Vector2u, float);
	~Animation();
	void Update(int, float, bool);

	sf::IntRect textRect;

private:
	sf::Vector2u imagecount;
	sf::Vector2u currentimage;

	float totaltime;
	float switchtime;

};

