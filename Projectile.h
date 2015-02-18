#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class Projectile : public VisibleGameObject
{
public:
	Projectile();
	virtual ~Projectile();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow &rw);

	bool Destroy();
private:
	float _velocity;
	float _timeBetweenShots;
	bool _shouldDestroy;
};