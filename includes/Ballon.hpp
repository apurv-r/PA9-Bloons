#pragma once
#include<SFML/Graphics.hpp>

#include"includes/MathHelper.h"
#include"SpriteManager.hpp"

class Balloon : public SpriteManager
{
public:
	Balloon(int level, sf::Vector2f pos) :SpriteManager("Resources\testingImage.jpg", pos) {};
	void moveTowards(sf::Vector2f goToPos, float speed);
};