#include "includes/Tower.hpp"

//Check this code most likely inaccurate
void Tower::update(float delta, sf::RenderWindow & window)
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
	window.draw(*this);
}

void Tower::addBalloonToList(Balloon& balloon)
{
	m_BalloonsInRange.push_back(&balloon);
}

Tower::Tower(sf::Vector2f pos, float xSize, float ySize, float radius)
	:sf::RectangleShape(sf::Vector2f(xSize, ySize)), m_pos(pos), m_Radius(radius)
{
	this->setOrigin(50, 50);
	m_display = false;
	this->setPosition(pos);
	this->setFillColor(sf::Color(255, 0, 255));
	m_lastThrownDart = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
}
//Checks using distance formula which is totally no correct
//However gets an expected result
bool Tower::isInRadius(sf::Vector2f otherPos, Balloon& b1)
{
	//Way to many )
	//Math is now correct plus adds 10 pixels to make it seem more visually appealing
	float distance = sqrt(abs((pow(((this->getPosition().x - (this->getSize().x / 2)) - (b1.getPos().x - b1.m_Object.getRadius() + 25)), 2) + (pow(((this->getPosition().y - (this->getSize().y / 2)) - (b1.getPos().y - b1.m_Object.getRadius() + 25)), 2)))));
	//std::cout << "Distance: " << distance << std::endl;
	if (distance < m_Radius)
	{
		addBalloonToList(b1);
		throwDart(b1);
		return true;
	}
	return false;
}
//Draws the radius 
void Tower::visualizeRadius(sf::RenderWindow& window)
{
	sf::CircleShape radiusVisual(m_Radius, 30);
	radiusVisual.setOrigin(m_Radius, m_Radius);
	radiusVisual.setPosition(this->getPosition().x, (this->getPosition().y));
	radiusVisual.setFillColor(sf::Color(0, 100, 0));
	window.draw(radiusVisual);
}


/// <summary>
/// Throw Dart
/// TODO: Nothing at the moment
/// </summary>
/// <param name="target"></param>
void Tower::throwDart(Balloon& target)
{
	//Gets the current time since epoch inwhich high_resolution_clocks epoch not sure what the actual epoch value is
	//Could be 01/01/1970 not that big of an issue
	std::chrono::milliseconds t_CurTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	//t_CurTime is going to be larger than m_lastThrownDart.
	if ((t_CurTime.count() - m_lastThrownDart.count()) > 800)
	{
		Dart* newDart = new Dart(50, 50, 5, target, this->getPosition());
		darts.push_back(newDart);
		m_lastThrownDart = t_CurTime;
	}
}
