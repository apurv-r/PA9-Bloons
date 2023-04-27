#pragma once
#include<SFML/Graphics.hpp>
#include"includes/Ballon.hpp"
class Boomerang :public sf::RectangleShape
{
public:
	Boomerang(float sizeX, float sizeY, float speed, float radius, sf::Vector2f spawnLocation);

	void changeSpeed(float speed) { m_speed = speed; };

	float getSpeed() { return m_speed; };

	void moveTowards(float delta);

	bool isCollided(std::vector<Balloon*> m_BalloonsInRange, Balloon* l_balloon);

	Balloon* getTarget() { return m_target; };

private:
	Balloon *m_target;
	float m_speed;
	float m_radius;
};