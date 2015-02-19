#include "stdafx.h"
#include "MainHUD.h"
#include "../Game.h"

MainHUD::MainHUD() :
_scoreValue(0),
_scoreText()
{
	if (!_font.loadFromFile("fonts/PCapTerminalBold.otf"))
	{
		std::cout << "Error loading font";
	}
	
}

MainHUD::~MainHUD(){}


void MainHUD::Draw(sf::RenderWindow &rw)
{
	rw.draw(_scoreText);
}

void MainHUD::Update(float elapsedTime)
{
	_scoreText.setString("SCORE: " + std::to_string(_scoreValue));
	_scoreText.setFont(_font);
	_scoreText.setCharacterSize(50);
	_scoreText.setColor(sf::Color::White);
	_scoreText.setPosition(10.f,10.f);
}

void MainHUD::IncrementScore()
{
	_scoreValue += 1;
}

void MainHUD::ResetScore()
{
	_scoreValue = 0;
}


bool MainHUD::ShouldPersist() const 
{
	return true;
}