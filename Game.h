#pragma once
#ifndef _GAME_H
#define _GAME_H

#include <memory>
#include "Projectile.h"
#include "Enemy.h"
#endif // !_GAME_H

class Game
{
private:
	void preloadTextures();
	void preloadPlatforms();
	void initPlayer();
	Projectile* createNewProjectile();
	std::unique_ptr<Enemy> createNewEnemy();
	void initEnemies();
	struct greater;
public:
	static void ResizeV(const sf::RenderWindow& window, sf::View& view);
	Game();
	~Game();
	void handle(sf::RenderWindow& window, sf::View& view);
};

