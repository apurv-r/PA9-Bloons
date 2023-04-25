#pragma once
#include<SFML/Graphics.hpp>
#include"includes/Ballon.hpp"
class Dart :public sf::RectangleShape
{
public:
	Dart(float sizeX, float sizeY, float speed, Balloon& target, sf::Vector2f spawnLocation);

	void changeSpeed(float speed) { m_speed = speed; };

	float getSpeed() { return m_speed; };

	void moveTowards(float delta);

	bool isCollided();

	Balloon* getTarget() { return m_target; };

private:
	Balloon *m_target;
	float m_speed;
};