#pragma once
#include "VisibleGameObject.h"

class Background : public VisibleGameObject
{
public:
	Background(int starSize);
	virtual ~Background();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);

private:
	float _velocity;
};