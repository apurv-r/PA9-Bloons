#include "Monkey.hpp"

bool Monkey::isInRadius(sf::Vector2f otherPos, Balloon& b1)
{
	//Way to many )
	//Math is now correct plus adds 10 pixels to make it seem more visually appealing
	float distance = sqrt(abs((pow(((this->getPosition().x - (this->getSize().x / 2)) - (b1.getPos().x - b1.m_Object.getRadius() + 25)), 2) + (pow(((this->getPosition().y - (this->getSize().y / 2)) - (b1.getPos().y - b1.m_Object.getRadius() + 25)), 2)))));
	//std::cout << "Distance: " << distance << std::endl;
	if (distance < m_Radius)
	{
		addBalloonToList(b1);
		this->throwDart(b1);
		return true;
	}
	return false;

}

void Monkey::visualizeRadius(sf::RenderWindow& window)
{
	sf::CircleShape radiusVisual(m_Radius, 30);

	radiusVisual.setPosition(this->getPosition().x - (m_Radius / 2) - (this->getSize().x / 2), (this->getPosition().y - (m_Radius / 2) - (this->getSize().y / 2)));
	radiusVisual.setFillColor(sf::Color(0, 100, 0));
	window.draw(radiusVisual);
}