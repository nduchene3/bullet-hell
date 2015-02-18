#include "stdafx.h"
#include "Player.h"
#include "../Game.h"

Player::Player() :
_velocity(600.f),
_noKeyWasPressed(true),
_playerHit(false),
_currentLives(3)
{
	Load("player.png");
	assert(IsLoaded());

}

Player::~Player(){}

void Player::Draw(sf::RenderWindow &rw)
{
	VisibleGameObject::Draw(rw);
}

void Player::Update(float elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		movement.y -= _velocity;
		_noKeyWasPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		movement.y += _velocity;
		_noKeyWasPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		movement.x -= _velocity;
		_noKeyWasPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		movement.x += _velocity;
		_noKeyWasPressed = false;
	}

	//collisions
	//handle left border
	if (GetSprite().getPosition().x <= 0 
		&& movement.x < 0)
	{
		movement.x = 0;
	}

	//handle right border
	if (GetSprite().getPosition().x >= Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width 
		&& movement.x > 0)
	{
		movement.x = 0;
	}

	//handle top border
	if (GetSprite().getPosition().y <= 0
		&& movement.y < 0)
	{
		movement.y = 0;
	}

	//handle bottom border
	if (GetSprite().getPosition().y >= Game::SCREEN_HEIGHT - GetSprite().getGlobalBounds().height
		&& movement.y > 0)
	{
		movement.y = 0;
	}


	GetSprite().move(movement * elapsedTime);

	_noKeyWasPressed = true;
}

void Player::HitPlayer()
{
	_playerHit = true;	
}

bool Player::IsPlayerHit()
{
	return _playerHit;
}

void Player::ResetPlayerState()
{
	_playerHit = false;
}

int Player::GetCurrentLives()
{
	return _currentLives;
}

void Player::ResetStartingPosition()
{
	sf::Vector2f returnVector;
	
	returnVector.x = Game::SCREEN_WIDTH / 2 - GetSprite().getGlobalBounds().width / 2;
	returnVector.y = Game::SCREEN_HEIGHT - 200.f;

	SetPosition(returnVector.x, returnVector.y);
}

bool Player::ShouldPersist() const
{
	return true;
}
