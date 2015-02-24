#pragma once
#include "Projectile.h"

class DualLaser : public Projectile
{
public:
	DualLaser();
	virtual ~DualLaser();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow &rw);
	virtual bool Destroy();

	void SetPosition(float x, float y);

private:
	sf::Sprite _secondSprite;
	float _velocity;
};