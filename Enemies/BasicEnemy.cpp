#include "stdafx.h"
#include "BasicEnemy.h"
#include "../Game.h"
#include "EnemyProjectile.h"
#include "../Player/Player.h"

BasicEnemy::BasicEnemy() :
_velocity(200.f),
_timeBetweenShots(0.f)
{
	Load("basicenemy.png");
	assert(IsLoaded());
}

BasicEnemy::~BasicEnemy(){}

void BasicEnemy::Draw(sf::RenderWindow &rw)
{
	VisibleGameObject::Draw(rw);
}

void BasicEnemy::Update(float elapsedTime)
{
	_timeBetweenShots += elapsedTime;
	sf::Vector2f movement(0.f, 0.f);

	if (_timeBetweenShots > 1.f)
	{
		//std::cout << "fire projectile" << std::endl;

		EnemyProjectile *shot = new EnemyProjectile();
		shot->SetPosition(GetSprite().getPosition().x + GetSprite().getGlobalBounds().width / 2 - shot->GetWidth() /2,
			GetSprite().getPosition().y + GetSprite().getGlobalBounds().height / 2);

		Game::GetGameObjectManager().Add("enemy_projectile_" + std::to_string(rand()), shot);

		_timeBetweenShots = 0.f;
	}

	movement.y += _velocity;
	GetSprite().move(movement * elapsedTime);


	//check for collision with player.
	Player *player = dynamic_cast<Player*>(Game::GetGameObjectManager().Get("player"));
	if (player != NULL)
	{
		if (!player->IsPlayerHit() && player->GetBoundingRect().intersects(GetSprite().getGlobalBounds()))
		{
			std::cout << "!!!!!!!!!!!!!!!!!!!PLAYER HIT!!!!!!!!!!!!!!!!!!!" << std::endl;

			player->HitPlayer();
		}
	}
}

