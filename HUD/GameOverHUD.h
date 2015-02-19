#pragma once
#include "../VisibleGameObject.h"

class GameOverHUD : public VisibleGameObject
{
public:
	GameOverHUD();
	virtual ~GameOverHUD();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);
	bool ShouldPersist() const;
private:
	sf::Text _gameOverText;
	sf::Font _font;
};