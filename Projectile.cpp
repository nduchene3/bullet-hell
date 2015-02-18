#include "stdafx.h"
#include "Projectile.h"
#include "BasicEnemy.h"
#include "Game.h"

Projectile::Projectile() :
_velocity(500.f),
_timeBetweenShots(1.f),
_shouldDestroy(false)
{
	Load("playerlaserbeam.png");
	assert(IsLoaded());
}

Projectile::~Projectile(){}

void Projectile::Draw(sf::RenderWindow &rw)
{
	VisibleGameObject::Draw(rw);
}

void Projectile::Update(float elapsedTime)
{

	sf::Vector2f movement(0.f, 0.f);

	movement.y -= _velocity;

	GetSprite().move(movement * elapsedTime);

	//check for collision with enemies.
	for each (auto item in Game::GetGameObjectManager().GetAll())
	{
		BasicEnemy* enemy = dynamic_cast<BasicEnemy*>(item.second);
		if (enemy != NULL)
		{
			if (enemy->GetBoundingRect().contains(GetSprite().getPosition()))
			{
				Game::GetGameObjectManager().Remove(item.first);
				_shouldDestroy = true;
			}
		}
	}
}

bool Projectile::Destroy()
{
	return _shouldDestroy;
}

