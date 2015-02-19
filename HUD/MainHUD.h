#pragma once
#include "../VisibleGameObject.h"

class MainHUD : public VisibleGameObject
{
public:
	MainHUD();
	~MainHUD();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);
	bool ShouldPersist() const;	
	void IncrementScore();
	void ResetScore();

private:
	int _scoreValue;
	sf::Text _scoreText;
	sf::Font _font;
};