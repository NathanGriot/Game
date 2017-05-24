#include <SFML\Graphics.hpp>
#include <iostream>
#include "player.h"
#include <vector>
#include "Platform.h"
#include <SFML/Audio.hpp>
#include "Enemy.h"
#include "Background.h"
#include "Projectile.h"
using namespace std;

//test view
static const float VHeight = 1000.0f;
void ResizeV(const sf::RenderWindow& window, sf::View& view)
{
	float ARation = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VHeight * ARation, VHeight);
}

int main()
{
	//text score
	int scorei = 0;
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
	void setLoop(bool loop);
	if (!music.openFromFile("background_music.wav"))
		return -1; // error
	music.setLoop(true);
	music.play();

	//Window
	//bool Nokeyispressed = false;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game", sf::Style::Default);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1920.0f, 1080.0f));

	//Texture
	sf::Texture playerTexture;
	sf::Texture EnemyTexture;

	//player
	playerTexture.loadFromFile("spritesheet_2.png");
	player Player(&playerTexture, sf::Vector2u(2, 9), 0.3f,300.0f,200.0f);

	//Enemy
	bool EnemyAlive = true;
	EnemyTexture.loadFromFile("Sprite.png");
	Enemy* enemy = new Enemy(&EnemyTexture, sf::Vector2u(1, 1), 0.3f, 300.0f, 200.0f);
	//Enemy TheEnemy(&EnemyTexture, sf::Vector2u(1, 1), 0.3f, 300.0f, 200.0f);

	//platforms 
	vector<Platform> Platforms; 
	Platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 500.0f), sf::Vector2f(0.0f, 500.0f)));
	Platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 500.0f), sf::Vector2f(1000.0f, 500.0f)));
	Platforms.push_back(Platform(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(300.0f, 200.0f)));
	Platforms.push_back(Platform(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(300.0f, 0.0f)));
	Platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f)));

	//background
	sf::Texture BackgroundTexture;
	BackgroundTexture.loadFromFile("city_background_night.png");
	Background background(&BackgroundTexture,sf::Vector2f(8192.0f,1024.0f), sf::Vector2f(0.0f, 0.0f));

	//projectiles
	//test
	//vector<Projectile> Projectiles;
	sf::Vector2f pose;
	pose.x = 10000000.0f; 
	pose.y = 10000000.0f;
	//
	Projectile Projectile1(Projectile(1000, pose));


	float deltatime = 0.0f;
	sf::Clock clock;
	/*sf::Vector2u textureSize = playerTexture.getSize();
	textureSize.x /= 9;
	textureSize.y /= 5;

	player.setTextureRect(sf::IntRect(0,0, textureSize.x, textureSize.y));

	//player.setFillColor(sf::Color::Blue); set la couleur
	*/
	
	while (window.isOpen())
	{
		deltatime = clock.restart().asSeconds();
		if (deltatime > 1.0f / 20.0f)
			deltatime = 1.0f / 20.0f;
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
			/*case sf::Event::Resized:
				cout << "New windows width: " << TheEvent.size.width << "New window height: " << TheEvent.size.height << endl;
				//	printf("New window width: %i New window height: %i \n", theevent.size.width, theevent.size.height);
				break;
			case sf::Event::TextEntered:
				if (TheEvent.text.unicode < 128)
				{
					printf("%c", TheEvent.text.unicode); // affiche la lettre de la touche
					//cout << theevent.text.unicode; // ceci affiche le code de la touche
				}
				*/

				if (TheEvent.type == TheEvent.Closed)
				{
					window.close();
				}
			}
		}
		/*
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		{
			window.clear();
			player.move(0.0f, -0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			window.clear();
			player.move(0.0f, 0.1f);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		{
			window.clear();

			player.move(-0.1f, 0.0f);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) )
		{
			window.clear();
			player.move(0.1f, 0.0f);
		}
		*/

		Player.Update(deltatime);
		//TheEnemy.Update(deltatime);
		if (enemy != NULL)
			enemy->Update(deltatime);

		sf::Vector2f direction;
		sf::Vector2f Direction;
		sf::Vector2f BodyPos;
		vector<Projectile> Projectiles;


		for (Platform& platform : Platforms)
		{
			if (platform.getcollision().checkcollision(Player.GetCollision(), direction, 1.0f))
			{
				Player.collision(direction);
			}
		}

		//if (Projectile1.getcollision().checkcollision(TheEnemy.GetCollision(), direction, 1.0f))
		if (enemy != NULL)
		{
			if (Projectile1.getcollision().checkcollision(enemy->GetCollision(), direction, 1.0f))
			{


			}
			else
			{
				scorei++;
				EnemyAlive == false;
				//TheEnemy.~Enemy();
				delete enemy;
				enemy = NULL;
				//TheEnemy = NULL;

			}
		}
		string score = std::to_string(scorei);
		Score.setString("score: " + score);
		for (Platform& platform : Platforms)
		{
			//if (platform.getcollision().checkcollision(TheEnemy.GetCollision(), Direction, 1.0f))
			if (enemy != NULL && platform.getcollision().checkcollision(enemy->GetCollision(), Direction, 1.0f))
			{
				enemy->collision(Direction);
			}
		}

		//if (Player.GetCollision().checkcollision(TheEnemy.GetCollision(), Direction, 1.0f))
		if (enemy != NULL && Player.GetCollision().checkcollision(enemy->GetCollision(), Direction, 1.0f))
		{
			enemy->collision(Direction);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			Projectile1.setpose(Player.getposition(),Player.getfacing());
		}
		view.setCenter(Player.getposition());
		background.draw(window);
		window.setView(view);
		Score.setPosition(Player.getcenterpos().x -500, Player.getcenterpos().y -550);
		Player.Draw(window);

		//if (TheEnemy != nullptr)
		if (enemy != NULL)
		{
			enemy->Draw(window);
		}

		for (Platform& platform : Platforms)
		{
			platform.draw(window);
		}

		Projectile1.update(deltatime);
		Projectile1.Draw(window);
		//Player.getcenterpos();
		window.draw(Score);
		window.display();
		window.clear();

	}
		
	return 0;
}