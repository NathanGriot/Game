#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imagecount = imageCount;
	this->switchtime = switchTime;
	totaltime = 0.0f;
	currentimage.x = 0;
	
	textRect.width = texture->getSize().x / imageCount.x;
	textRect.height = texture->getSize().y / imageCount.y;
}

Animation::~Animation()
{
}

void Animation::Update(int row, float deltatime, bool facing)
{
	currentimage.y = row;
	totaltime += deltatime;

	if (totaltime >= switchtime)
	{
		totaltime -= switchtime;
		currentimage.x++;
		if (currentimage.x >= imagecount.x)
		{
			currentimage.x = 0;
		}
	}
	textRect.top = currentimage.y * textRect.height;
	if (facing)
	{
		textRect.left = currentimage.x * textRect.width;
		textRect.width = abs(textRect.width);
	}
	else
	{
		textRect.left = (currentimage.x+1) * abs(textRect.width);
		textRect.width = -abs(textRect.width);
	}
	

}

