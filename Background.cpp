#include "stdafx.h"
#include "Background.h"

Background::Background(int starSize) 
{
	switch (starSize)
	{
	case 1:
		Load("background-size1.png");
		assert(IsLoaded());
		_velocity = 50.f;
		break;
	case 2:
		Load("background-size2.png");
		assert(IsLoaded());
		_velocity = 200.f;
		break;
	case 4:
		Load("background-size4.png");
		assert(IsLoaded());
		_velocity = 400.f;
		break;
	default:
		break;
	}	
}

Background::~Background(){}

void Background::Update(float elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);

	movement.y += _velocity;

	auto position = GetSprite().getPosition().y;
	if (position > -0.f)
	{
		GetSprite().setPosition(0.f, -768.f);
	}


	GetSprite().move(movement * elapsedTime);


}

void Background::Draw(sf::RenderWindow &rw)
{
	VisibleGameObject::Draw(rw);
}

bool Background::ShouldPersist() const
{
	return true;
}