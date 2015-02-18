#pragma once
#include "VisibleGameObject.h"

class Background : public VisibleGameObject
{
public:
	Background(int starSize);
	virtual ~Background();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);
	bool ShouldPersist() const;

private:
	float _velocity;
};