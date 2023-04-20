#include"includes/Ballon.hpp"
#include<iostream>

//Takes in a speed and a vector and calculates the direction vector
//Which will be less than 1 inwhich the object is to move towards
void Balloon::moveTowards(sf::Vector2f goToVector, float speed)
{
	//The math works for some reason
	sf::Vector2f dir = (-1.0f*MathHelper::MathHelp::normalize((this->getPos() - goToVector)));
	//std::cout << "X: " << dir.x << " Y: " << dir.y << std::endl;
	this->m_Object.move(speed * dir);
}