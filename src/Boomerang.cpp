#include "includes/Boomerang.hpp"
#include"includes/MathHelper.h"

Boomerang::Boomerang(float sizeX, float sizeY, float speed, float radius, sf::Vector2f spawnLocation)
	:sf::RectangleShape(sf::Vector2f(sizeX, sizeY))
{
	this->setPosition(spawnLocation);
	m_speed = speed;
	m_radius = radius;
}

void Boomerang::moveTowards(float delta)
{
	//The math works for some reason
	sf::Vector2f dir = (-1.0f * MathHelper::MathHelp::circleMath(MathHelper::MathHelp::normalize(this->getPosition()), m_radius));
	//std::cout << "X: " << dir.x << " Y: " << dir.y << std::endl;
	this->move(m_speed * dir * delta);
}

bool Boomerang::isCollided(std::vector<Balloon*> m_BalloonsInRange, Balloon* l_balloon)
{
	for (Balloon* b : m_BalloonsInRange) {
		if (this->getGlobalBounds().intersects(b->m_Object.getGlobalBounds())) {
			l_balloon = b;
			return true;
		}
		else {
			l_balloon = nullptr;
			return false;
		}
	}

}