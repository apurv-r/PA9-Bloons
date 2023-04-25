#include"includes/Ballon.hpp"
#include<iostream>

void Balloon::update(float delta, sf::RenderWindow& window)
{
	if (!(this->m_health <= 0))
	{
		moveTowards(coords[coordIndex], m_speed*delta);
		if (MathHelper::MathHelp::isAround(this->getPos(), coords[coordIndex], 10))
		{
			std::cout << "HERE" << std::endl;
			coordIndex++;
		}
		Render(window);
	}
	else
	{
		//Should never be called here just incase
		//delete this is not possible for memory reasons.
		//Big crash happens if you use delete this
		this->m_Object.setPosition(1000, 10000);
	}
}

//Takes in a speed and a vector and calculates the direction vector
//Which will be less than 1 inwhich the object is to move towards
void Balloon::moveTowards(sf::Vector2f goToVector, float speed)
{
	//normalizes the vector between the two positions.
	//Then has to multiply by -1 because of how the math ended up working out.
	sf::Vector2f dir = (-1.0f*MathHelper::MathHelp::normalize((this->getPos() - goToVector)));

	//Calls the sf move function using the values already given
	this->m_Object.move(speed * dir);
}