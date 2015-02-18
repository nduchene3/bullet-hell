#include "stdafx.h"
#include "VisibleGameObject.h"
#include "Game.h"


VisibleGameObject::VisibleGameObject() :_isLoaded(false)
{
}

VisibleGameObject::~VisibleGameObject()
{

}

void VisibleGameObject::Load(std::string filename)
{
	filename = "textures/" + filename;

	//implementing a basic image caching algorithim.
	auto iter = _images.find(filename);
	if (iter == _images.end())
	{
		sf::Texture texture;
		if (!texture.loadFromFile(filename))
		{
			std::cout << "image failed to load" << std::endl;
			assert(false);
		}

		auto img = _images.insert(std::pair<std::string, sf::Texture>(filename, texture)).first;
		std::cout << filename + ": loaded from file and added to cache." << std::endl;
		_sprite.setTexture(img->second);
		_isLoaded = true;		
	}
	else
	{
		//std::cout << filename + ": loaded from cache" << std::endl;
		_sprite.setTexture(iter->second);
		_isLoaded = true;
	}

	_imageKey = filename;
}

void VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
	renderWindow.draw(_sprite);
}

void VisibleGameObject::Update(float elapsedTime)
{
}

void VisibleGameObject::SetPosition(float x, float y)
{
	if (_isLoaded)
	{
		return _sprite.setPosition(x, y);
	}
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
	if (_isLoaded)
	{
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::GetSprite()
{
	return _sprite;
}

bool VisibleGameObject::IsLoaded() const
{
	return _isLoaded;
}

float VisibleGameObject::GetHeight() const
{
	return _sprite.getLocalBounds().height;
}

float VisibleGameObject::GetWidth() const
{
	return _sprite.getLocalBounds().width;
}

sf::FloatRect VisibleGameObject::GetBoundingRect() const
{
	return _sprite.getGlobalBounds();
}

bool VisibleGameObject::ShouldPersist() const
{
	return false;
}

//the basic image cache
std::map<std::string, sf::Texture> VisibleGameObject::_images;
