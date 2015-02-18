#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"
#include "Player.h"


GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
	_gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::Remove(std::string name)
{
	auto results = _gameObjects.find(name);
	if (results != _gameObjects.end())
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

void GameObjectManager::Reset()
{
	/*
	typedef std::map<std::string, VisibleGameObject*>::iterator it_type;

	for (it_type iterator = _gameObjects.begin();
	iterator != _gameObjects.end();
	iterator = _gameObjects.erase(iterator))
	{
	delete iterator->second;
	}
	*/

	auto iterator = _gameObjects.begin();
	while (iterator != _gameObjects.end())
	{
		if (iterator->first == "player")
		{
			auto player = dynamic_cast<Player*>(iterator->second);
			player->ResetStartingPosition();
		}

		if (iterator->first != "bg1" 
			&& iterator->first != "bg2" 
			&& iterator->first != "bg4" 
			&& iterator->first != "player")
		{
			delete iterator->second;
			iterator = _gameObjects.erase(iterator);
		}
		else
		{
			iterator++;
		}
	}
}

VisibleGameObject* GameObjectManager::Get(std::string name) const
{
	auto results = _gameObjects.find(name);
	if (results == _gameObjects.end())
	{
		return NULL;
	}
	return results->second;
}

int GameObjectManager::GetObjectCount() const
{
	return _gameObjects.size();
}

void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
	auto itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}
}

void GameObjectManager::UpdateAll()
{
	auto itr = _gameObjects.begin();
	float timeDelta = clock.restart().asSeconds();
	//std::cout << "time delta: " << timeDelta << std::endl;
	while (itr != _gameObjects.end())
	{
		itr->second->Update(timeDelta);
		itr++;
	}
}

void GameObjectManager::ResetClock()
{
	//need to mke sure clock is restarted before game state shift to playing.
	clock.restart();
}

float GameObjectManager::GetTimeDelta(){
	return clock.getElapsedTime().asSeconds();
}

std::map<std::string, VisibleGameObject*> GameObjectManager::GetAll()
{
	return _gameObjects;
}