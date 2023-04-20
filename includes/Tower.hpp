#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>


class Tower : public sf::RectangleShape
{
public:
	Tower(sf::Vector2f pos, float xSize, float ySize)
		:sf::RectangleShape(sf::Vector2f(xSize, ySize))
	{
		this->setPosition(pos);
		this->setFillColor(sf::Color(255, 0, 255));
	}
	//Checks using distance formula which is totally no correct
	//However gets an expected result
	bool isInRadius(sf::Vector2f otherPos, float radius,Balloon& b1)
	{

		//Way to many )
		//Math is not correct at all but looks somewhat nice in the actual product
		float distance = sqrt(abs((pow((this->getPosition().x-(b1.getPos().x-b1.m_Object.getRadius()*1.5)), 2) + (pow((this->getPosition().y - (b1.getPos().y- b1.m_Object.getRadius()*1.5)), 2)))));
		std::cout << "Distance: " << distance << std::endl;
		if (distance < radius)
		{
			return true;
		}
		return false;
	}
	//Draws the radius 
	void visualizeRadius(float radius, sf::RenderWindow & window,Balloon&b1)
	{
		sf::CircleShape radiusVisual(radius, 30);
		radiusVisual.setPosition(this->getPosition().x - (radius/2), this->getPosition().y - (radius/2));
		if (isInRadius(b1.getPos(), 250,b1))
			radiusVisual.setFillColor(sf::Color(100, 0, 0));
		else
			radiusVisual.setFillColor(sf::Color(0, 100, 0));

		window.draw(radiusVisual);
	}
};