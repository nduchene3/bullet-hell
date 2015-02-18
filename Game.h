#include "stdafx.h"
#include "GameObjectManager.h"


class Game
{
public:
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;

	const static int MAX_PROJECTILES = 3;

	static void Start();
	static sf::RenderWindow& GetWindow();
	const static sf::Event& GetInput();

	static GameObjectManager& GetGameObjectManager();

	
private:
	static bool IsExiting();
	static void GameLoop();

	enum GameState{
		Playing, Exiting, GameOver
	};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static GameObjectManager _gameObjectManager;

	static int _projectileCounter;
	static float _elapsedTime;

	static float _enemyTimer;
};