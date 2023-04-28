#pragma once
#include<SFML/Graphics.hpp>
#include<chrono>
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

	std::chrono::milliseconds getTimeCreated() { return m_timeCreated; };

	void setTimeCreated(std::chrono::milliseconds newTime) { m_timeCreated = newTime; };

private:
	std::chrono::milliseconds m_timeCreated;
	Balloon *m_target;
	float m_speed;
};