#pragma once
#include "VisibleGameObject.h"

class Player : public VisibleGameObject
{
public:
	Player();
	virtual ~Player();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);
	bool ShouldPersist() const;

	void HitPlayer();
	bool IsPlayerHit();
	void ResetPlayerState();
	int GetCurrentLives();
	void ResetStartingPosition();

private:
	float _velocity;
	bool _noKeyWasPressed;
	bool _playerHit;
	int _currentLives;
};