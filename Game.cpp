#include "stdafx.h"
#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "Projectile.h"
#include "BasicEnemy.h"
#include "EnemyProjectile.h"

void Game::Start()
{
	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Bullet Hell");

	Background *background1 = new Background(1);
	background1->SetPosition(0.f, -768.f);
	_gameObjectManager.Add("bg1", background1);

	Background *background2 = new Background(2);
	background2->SetPosition(0.f, -768.f);
	_gameObjectManager.Add("bg2", background2);

	Background *background4 = new Background(4);
	background4->SetPosition(0.f, -768.f);
	_gameObjectManager.Add("bg4", background4);

	Player *player = new Player();
	player->ResetStartingPosition();
	_gameObjectManager.Add("player", player);

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);

	switch (_gameState)
	{

	case GameState::Playing:
	{
		_mainWindow.clear(sf::Color(0, 0, 0, 255));

		auto player = dynamic_cast<Player*>(_gameObjectManager.Get("player"));
		if (player->IsPlayerHit())
		{
			_gameState = Game::GameOver;
			return;
		}

		if (currentEvent.type == sf::Event::KeyPressed)
		{
			//if the key is spacebar, fire a player projectile.
			if (currentEvent.key.code == sf::Keyboard::Space)
			{
				std::cout << "fire" << std::endl;
				auto player = _gameObjectManager.Get("player");
				
				Projectile *bullet = new Projectile();
				bullet->SetPosition(player->GetPosition().x + (player->GetWidth() / 2) - (bullet->GetWidth() / 2), player->GetPosition().y);

				std::string key = "bullet_" + std::to_string(rand());
				_gameObjectManager.Add(key, bullet);
			}

			//if it is the escape key, we exit the program.
			if (currentEvent.key.code == sf::Keyboard::Escape)
			{
				sf::View view = _mainWindow.getDefaultView();
				_mainWindow.setView(view);
				_gameState = Game::Exiting;
			}
		}

		//determine if it is time to spawn BasicEnemy
		_enemyTimer += _gameObjectManager.GetTimeDelta();
		if (_enemyTimer > 2.f)
		{
			std::cout << "launching basic enemy" << std::endl;
			BasicEnemy *enemy = new BasicEnemy();
			enemy->SetPosition((rand() % Game::SCREEN_WIDTH - 500.f) + 500.f, 0 - enemy->GetHeight());
			_gameObjectManager.Add("enemy_" + std::to_string(rand()), enemy);
			_enemyTimer = 0.f;
		}

		//clean up objects that have left the screen.
		for each (auto item in _gameObjectManager.GetAll())
		{
			Projectile* bullet = dynamic_cast<Projectile*>(item.second);
			BasicEnemy* enemy = dynamic_cast<BasicEnemy*>(item.second);
			EnemyProjectile* enemy_bullet = dynamic_cast<EnemyProjectile*>(item.second);

			if (bullet != NULL)
			{
				if (bullet->GetPosition().y < 0 || bullet->Destroy())
				{
					std::cout << "remove bullet" << std::endl;
					_gameObjectManager.Remove(item.first);
				}
			}

			if (enemy != NULL)
			{
				if (enemy->GetPosition().y > Game::SCREEN_HEIGHT)
				{
					std::cout << "remove enemy" << std::endl;
					_gameObjectManager.Remove(item.first);
				}
			}

			if (enemy_bullet != NULL)
			{
				if (enemy_bullet->GetPosition().y > Game::SCREEN_HEIGHT)
				{
					std::cout << "remove enemy projectile" << std::endl;
					_gameObjectManager.Remove(item.first);
				}
			}
		}

		//update and draw all game objects.
		_gameObjectManager.UpdateAll();
		_gameObjectManager.DrawAll(_mainWindow);

		//refresh the display window.
		_mainWindow.display();

		//did the player press the "X" in the upper right corner
		if (currentEvent.type == sf::Event::Closed)
		{
			_gameState = Game::Exiting;
		}
		break;	
	} //end case GameState::Playing
	case GameState::GameOver:

		if (currentEvent.type == sf::Event::KeyPressed)
		{
			//if the key is spacebar, reset game.
			if (currentEvent.key.code == sf::Keyboard::Return)
			{
				std::cout << "resetting game" << std::endl;				
				auto bg1 = _gameObjectManager.Get("bg1");
				auto bg2 = _gameObjectManager.Get("bg2");
				auto bg4 = _gameObjectManager.Get("bg4");
				auto player = dynamic_cast<Player*>(_gameObjectManager.Get("player"));
				player->ResetPlayerState();

				_gameObjectManager.Reset();

				_mainWindow.clear(sf::Color(0, 0, 0, 255));
				_gameObjectManager.UpdateAll();
				_gameObjectManager.DrawAll(_mainWindow);
				_mainWindow.display();

				_gameState = GameState::Playing;
				
			}

			//if it is the escape key, we exit the program.
			if (currentEvent.key.code == sf::Keyboard::Escape)
			{
				sf::View view = _mainWindow.getDefaultView();
				_mainWindow.setView(view);
				_gameState = Game::Exiting;
			}
		}


		//did the player press the "X" in the upper right corner
		if (currentEvent.type == sf::Event::Closed)
		{
			_gameState = Game::Exiting;
		}
		break;
	} //end switch
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

const sf::Event& Game::GetInput()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	return currentEvent;
}

bool Game::IsExiting()
{
	if (_gameState == GameState::Exiting)
	{
		return true;
	}
	else
	{
		return false;
	}
}

GameObjectManager& Game::GetGameObjectManager()
{
	return _gameObjectManager;
}



Game::GameState Game::_gameState = GameState::Playing;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;

int Game::_projectileCounter = 0;
float Game::_elapsedTime = 0.f;
float Game::_enemyTimer = 0.f;