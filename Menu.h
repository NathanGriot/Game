#pragma once
#ifndef _MENU_H
#define _MENU_H

#include "SFML/Graphics.hpp"
#endif // !_MENU_H

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
	Menu(sf::RenderWindow& window);
	~Menu();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

};