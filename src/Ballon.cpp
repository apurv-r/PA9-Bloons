#include"includes/Ballon.hpp"
#include<iostream>

void Balloon::update(float delta, sf::RenderWindow& window)
{
	if (!(this->m_health <= 0))
	{
		moveTowards(coords[coordIndex], m_speed);
		if (MathHelper::MathHelp::isAround(this->getPos(), coords[coordIndex], 10))
		{
			std::cout << "HERE" << std::endl;
			coordIndex++;
		}
		Render(window);
	}
	else
	{
		//delete this;
		this->m_Object.setPosition(1000, 10000);
	}
}

//Takes in a speed and a vector and calculates the direction vector
//Which will be less than 1 inwhich the object is to move towards
void Balloon::moveTowards(sf::Vector2f goToVector, float speed)
{
	//The math works for some reason
	sf::Vector2f dir = (-1.0f*MathHelper::MathHelp::normalize((this->getPos() - goToVector)));
	//std::cout << "X: " << dir.x << " Y: " << dir.y << std::endl;
	this->m_Object.move(speed * dir);
}