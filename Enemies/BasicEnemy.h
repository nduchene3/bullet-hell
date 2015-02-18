#pragma once
#include "../VisibleGameObject.h"

class BasicEnemy : public VisibleGameObject
{
public: 
	BasicEnemy();
	virtual ~BasicEnemy();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);

private:
	float _velocity;
	float _timeBetweenShots;
	float _startingXCoord;

};