
#include "stdafx.h"
#include "DualLaser.h"
#include "../Enemies/BasicEnemy.h"
#include "../Game.h"
#include "../HUD/MainHUD.h"

DualLaser::DualLaser() :
_velocity(500.f)
{
	Load("playerlaserbeam.png");
	assert(IsLoaded());

	_secondSprite = sf::Sprite(GetSprite());

	Projectile::shouldDestroy = false;
}

DualLaser::~DualLaser(){}

void DualLaser::SetPosition(float x, float y)
{
	//set first position
	GetSprite().setPosition(x - 30, y);

	//set second position
	_secondSprite.setPosition(x + 30, y);
}


void DualLaser::Update(float elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);

	movement.y -= _velocity;

	GetSprite().move(movement * elapsedTime);
	_secondSprite.move(movement * elapsedTime);

	//check for collision with enemies.
	for each (auto item in Game::GetGameObjectManager().GetAll())
	{
		BasicEnemy* enemy = dynamic_cast<BasicEnemy*>(item.second);
		if (enemy != NULL)
		{
			if (enemy->GetBoundingRect().contains(GetSprite().getPosition())
				|| enemy->GetBoundingRect().contains(_secondSprite.getPosition()))
			{
				Game::GetGameObjectManager().Remove(item.first);
				shouldDestroy = true;

				//increment score
				auto hud = dynamic_cast<MainHUD*>(Game::GetGameObjectManager().Get("hud"));
				hud->IncrementScore();
			}
		}
	}
}

void DualLaser::Draw(sf::RenderWindow &rw)
{
	rw.draw(GetSprite());
	rw.draw(_secondSprite);
}

bool DualLaser::Destroy()
{
	return shouldDestroy;
}