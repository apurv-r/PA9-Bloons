#pragma once
#include<SFML/Graphics.hpp>

#include"includes/MathHelper.h"
#include"SpriteManager.hpp"

class Balloon : public SpriteManager
{
public:
	Balloon(int level, sf::Vector2f pos) :SpriteManager("Resources/testingImage.jpg", pos) 
	{
		m_speed = .5;
		m_health = level;
		coords.push_back(sf::Vector2f(1000, 500));
		coords.push_back(sf::Vector2f(500, 1000));
	};
	void update(float delta, sf::RenderWindow& window);

	void moveTowards(sf::Vector2f goToPos, float speed);
	int getHealth() { return m_health; }
	void changeHealth(int change) { m_health -= change; };
private:

	float m_speed;
	int m_health;
	int coordIndex = 0;
	std::vector<sf::Vector2f> coords;
};