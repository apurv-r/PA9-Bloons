#pragma once
#include<SFML/Graphics.hpp>

#include"includes/MathHelper.h"
#include"SpriteManager.hpp"

class Balloon : public SpriteManager
{
public:
	Balloon(int level, sf::Vector2f pos, std::vector<sf::Vector2f> inputted_coords) :SpriteManager("Resources/testingImage.jpg", pos, sf::Vector2f(100,100))
	{
		m_speed = 2;
		m_health = level;
		m_InitialHealth = level;
		coords = inputted_coords;
	};
	void update(float delta, sf::RenderWindow& window);

	void moveTowards(sf::Vector2f goToPos, float speed);
	int getHealth() { return m_health; }
	int getInitHealth() { return m_InitialHealth; }
	void changeHealth(int change) { m_health -= change; };
private:

	float m_speed;
	int m_health;
	int m_InitialHealth;
	int coordIndex = 0;
	std::vector<sf::Vector2f> coords;
};