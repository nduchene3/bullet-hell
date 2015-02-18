#pragma once
#include "stdafx.h"

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow & window);
	virtual void Update(float elapsedTime) = 0;

	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition() const;
	virtual float GetWidth() const;
	virtual float GetHeight() const;

	virtual sf::Rect<float> GetBoundingRect() const;
	virtual bool IsLoaded() const;


protected:
	sf::Sprite& GetSprite();

private:
	sf::Sprite  _sprite;
	std::string _imageKey;
	bool _isLoaded;
	static std::map<std::string, sf::Texture> _images;
};