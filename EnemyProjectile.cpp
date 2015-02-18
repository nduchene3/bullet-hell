#include "stdafx.h"
#include "EnemyProjectile.h"
#include "Player.h"
#include "Game.h"

EnemyProjectile::EnemyProjectile() :
_velocity(500.f)
{
	Load("redlaserbeam.png");
	assert(IsLoaded());
}

EnemyProjectile::~EnemyProjectile(){}

void EnemyProjectile::Draw(sf::RenderWindow &rw)
{
	VisibleGameObject::Draw(rw);
}

void EnemyProjectile::Update(float elapsedTime)
{

	sf::Vector2f movement(0.f, 0.f);

	movement.y += _velocity;

	GetSprite().move(movement * elapsedTime);

	//check for collision with player.
	Player *player = dynamic_cast<Player*>(Game::GetGameObjectManager().Get("player"));
	if (player != NULL)
	{
		if (!player->IsPlayerHit() && player->GetBoundingRect().contains(GetSprite().getPosition()))
		{
			std::cout << "!!!!!!!!!!!!!!!!!!!PLAYER HIT!!!!!!!!!!!!!!!!!!!" << std::endl;

			player->HitPlayer();
		}
	}



}