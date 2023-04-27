#include "includes/Monkey.hpp"

bool Monkey::isInRadius(sf::Vector2f otherPos, Balloon& b1)
{
	//Way to many )
	//Math is now correct plus adds 10 pixels to make it seem more visually appealing
	float distance = sqrt(abs((pow(((this->m_Object.getPosition().x) - (b1.getPos().x)), 2) + (pow((this->m_Object.getPosition().y) - (b1.getPos().y), 2)))));
	//std::cout << "Distance: " << distance << std::endl;
	if (distance < m_Radius)
	{
		addBalloonToList(b1);
		this->throwDart(b1);
		this->m_LastBalloonPos = m_BalloonsInRange[0]->getPos();
		return true;
	}
	return false;

}

void Monkey::visualizeRadius(sf::RenderWindow& window)
{
	sf::CircleShape radiusVisual(m_Radius, 30);
	radiusVisual.setOrigin(sf::Vector2f(m_Radius-m_Xsize/2, m_Radius-m_YSize/2));
	radiusVisual.setPosition(this->m_Object.getPosition().x, (this->m_Object.getPosition().y));
	radiusVisual.setFillColor(sf::Color(0, 100, 0));
	window.draw(radiusVisual);
}

void Monkey::update(float delta, sf::RenderWindow& window)
{
	if (m_display)
	{
		visualizeRadius(window);
	}
	for (int i = 0; i < darts.size(); i++)
	{
		if (darts[i]->isCollided())
		{
			//Deletes the data that is the cause of a collision
			//should this check whether the balloon is dead
			//Well Dart should == nullptr and as such should destroy itself
			darts[i]->getTarget()->changeHealth(1);
			darts.erase(darts.begin() + i);
		}
	}
	for (Dart* d : darts)
	{
		d->moveTowards(delta);
		window.draw(*d);
	}
	//Rotate towards target
	if (m_BalloonsInRange.size() >0)
	{
		double angle = std::atan2(this->m_Object.getPosition().y + this->m_BalloonsInRange[0]->getPos().y,this->m_Object.getPosition().x + this->m_BalloonsInRange[0]->getPos().x);
		std::cout << angle*180/3.14 << std::endl;
		this->m_Object.setRotation(angle*180/3.14);
	}
	this->Render(window);
	//window.draw(this->m_Object);
}
