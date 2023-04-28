#include "includes/Dart.hpp"
#include"includes/MathHelper.h"

Dart::Dart(float sizeX, float sizeY, float speed, Balloon& target, sf::Vector2f spawnLocation)
	:sf::RectangleShape(sf::Vector2f(sizeX, sizeY))
{
	this->setPosition(spawnLocation);
	m_speed = speed;
	m_target = &target;
	m_FirstCalc = true;
}

void Dart::moveTowards(float delta)
{
	//The math works for some reason
	if (m_FirstCalc)
	{
		dir = (-1.0f * MathHelper::MathHelp::normalize((this->getPosition() - m_target->getPos())));
		m_FirstCalc = false;
	}
	//std::cout << "X: " << dir.x << " Y: " << dir.y << std::endl;
	this->move(m_speed * dir*delta);
}

bool Dart::isCollided()
{
	if (this->getGlobalBounds().intersects(m_target->getGlobalBounds()))
		return true;
	else
		return false;
}