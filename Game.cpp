#include <SFML\Graphics.hpp>
#include <iostream>
#include <memory>
#include "Player.h"
#include <vector>
#include "Platform.h"
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Enemy.h"
#include "Background.h"
#include "Projectile.h"
#include "Game.h"
using namespace std;

// Textures
sf::Texture* playerTexture;
sf::Texture* enemyTexture;

// Player
Player* player;

// Enemies
vector<std::unique_ptr<Enemy> > enemies;

// Platforms
vector<Platform*> platforms;

// Timing values
double elapsedTime; // Total elapsed time in seconds.
double lastFireTime;

void Game::preloadTextures()
{
	playerTexture = new sf::Texture();
	playerTexture->loadFromFile("spritesheet_2.png");

	enemyTexture = new sf::Texture();
	enemyTexture->loadFromFile("Sprite.png");
}

void Game::preloadPlatforms()
{
	platforms.push_back(new Platform(nullptr, sf::Vector2f(100.0f, 1500.0f), sf::Vector2f(0.0f, 500.0f)));
	platforms.push_back(new Platform(nullptr, sf::Vector2f(100.0f, 1500.0f), sf::Vector2f(1000.0f, 500.0f)));
	platforms.push_back(new Platform(nullptr, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(300.0f, 250.0f)));
	//platforms.push_back(new Platform(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(300.0f, 0.0f)));
	platforms.push_back(new Platform(nullptr, sf::Vector2f(1000.0f, 600.0f), sf::Vector2f(500.0f, 700.0f)));
}

void Game::initPlayer()
{
	player = new Player(playerTexture, sf::Vector2u(2, 9), 0.3f, 300.0f, 200.0f);
}

Projectile* Game::createNewProjectile()
{
	return new Projectile(1000, sf::Vector2f(10000000.0f, 10000000.0f));
}

std::unique_ptr<Enemy> Game::createNewEnemy() // FIXME - Literally 0 sense like that (maybe use parameters for location?)
{
	return std::make_unique<Enemy>(enemyTexture, sf::Vector2u(1, 1), 0.3f, 150.0f, 200.0f);
}

void Game::initEnemies()
{
	enemies.push_back(createNewEnemy()); // Initializes first enemy.
}

//test view
static const float VHeight = 1000.0f;
void Game::ResizeV(const sf::RenderWindow& window, sf::View& view)
{
	float ARation = window.getSize().x / (float)window.getSize().y;
	view.setSize(VHeight * ARation, VHeight);
}

// for std::sort
struct Game::greater
{
	template<class T>
	bool operator()(T const &a, T const &b) const { return a > b; }
};

Game::Game()
{
}

Game::~Game()
{
	//TODO
}

void Game::handle(sf::RenderWindow& window, sf::View& view)
{
	elapsedTime = 0.0;
	lastFireTime = 0.0;

	//text score
	int score = 0;
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	sf::Text Score;
	Score.setFont(font);
	Score.setString("Score: ");
	Score.setCharacterSize(30);
	Score.setStyle(sf::Text::Regular);
	Score.setFillColor(sf::Color::Red);

	//music
	sf::Music music;
	if (!music.openFromFile("background_music.wav"))
		return; // error
	music.setLoop(true);
	music.play();

	//Window
	//bool Nokeyispressed = false;

	preloadTextures();
	preloadPlatforms();
	initPlayer();
	initEnemies();

	// Background
	sf::Texture BackgroundTexture;
	BackgroundTexture.loadFromFile("city_background_night.png");
	Background background(&BackgroundTexture, sf::Vector2f(8192.0f, 1024.0f), sf::Vector2f(0.0f, 0.0f));

	// Projectiles
	vector<Projectile*> projectiles;

	float deltaTime = 0.0;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;
		sf::Event TheEvent;
		while (window.pollEvent(TheEvent))
		{
			switch (TheEvent.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeV(window, view);
				break;
			}

			if (TheEvent.type == TheEvent.Closed)
				window.close();
		}

		elapsedTime += deltaTime;

		player->update(deltaTime);
		for (auto& enemy : enemies) // Tick-update enemies.
			enemy->update(deltaTime);

		sf::Vector2f direction;
		sf::Vector2f Direction;
		sf::Vector2f BodyPos;

		if (lastFireTime < elapsedTime && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			lastFireTime = elapsedTime + 0.5;
			projectiles.push_back(createNewProjectile());
			projectiles.at(projectiles.size() - 1)->setpose(player->getPosition(), player->getFacing());
		}

		for (Platform* platform : platforms) // OK
		{
			if (platform->getCollision().checkCollision(player->GetCollision(), direction, 1.0f))
				player->collision(direction);
		}


		// Iterate through enemies and projectiles and detect if projectiles have encountered any enemy.
		for (auto itor = enemies.begin(); itor != enemies.end();)
		{
			auto& enemy = *itor;

			if (enemy->isDead())
			{
				itor = enemies.erase(itor);
				continue;
			}

			itor++;

			if (enemy->isDecaying())
			{
				continue;
			}

			for (auto itorProj = projectiles.begin(); itorProj != projectiles.end(); itorProj++)
			{
				Projectile* projectile = *itorProj;

				if (projectile->getCollision().checkCollision(enemy->getCollision(), direction, 1.0f))
				{
					// Delay the deletion so we delete them after the iteration.
					enemy->doDie();
					delete projectile;
					projectiles.erase(itorProj);

					score++;
					break;
				}
			}
		}

		// Collision of enemies with platforms.
		for (Platform* platform : platforms)
		{
			for (auto& enemy : enemies)
			{
				if (platform->getCollision().checkCollision(enemy->getCollision(), Direction, 1.0f))
					enemy->collision(Direction);
			}
		}

		// Collision with player. TODO

		// Calculate the score and assign it onto a string.
		string scoreStr = std::to_string(score);
		Score.setString("Score: " + scoreStr);

		// ======================== DRAWING =======================================

		view.setCenter(player->getPosition());
		background.draw(window);
		window.setView(view);
		Score.setPosition(player->getCenterPos().x - 500, player->getCenterPos().y - 550);
		player->Draw(window);

		if (enemies.size() < 1) // FIXME - Creating an enemy after the other one just died is weird.
			enemies.push_back(createNewEnemy());

		// Draw enemies and update their tick.
		for (auto& enemy : enemies)
		{
			enemy->update(deltaTime);
			enemy->Draw(window);
		}

		// Draw platforms.
		for (Platform* platform : platforms)
			platform->draw(window);

		// Draw projectiles and update their tick.
		for (Projectile* projectile : projectiles)
		{
			projectile->update(deltaTime);
			projectile->draw(window);
		}

		//Player.getcenterpos();

		// Draw the score.
		window.draw(Score);

		// Display the window and dispose of the scene for the next frame.
		window.display();
		window.clear();
	}
}