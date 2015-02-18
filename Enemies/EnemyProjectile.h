#pragma once
#include "../VisibleGameObject.h"

class EnemyProjectile : public VisibleGameObject
{
public:
	EnemyProjectile();
	virtual ~EnemyProjectile();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow &rw);
private:
	float _velocity;
};