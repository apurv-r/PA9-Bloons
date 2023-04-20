#pragma once
#include<SFML/Graphics.hpp>
#include"includes/Ballon.hpp"
class Dart :public sf::RectangleShape
{
public:
	Dart(float sizeX, float sizeY, float speed, Balloon& target);

	void moveTowards(float delta);

	bool isCollided();

private:
	Balloon *m_target;
	float m_speed;
};