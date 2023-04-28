#include "includes/Tower.hpp"

//Check this code most likely inaccurate
void Tower::update(float delta, sf::RenderWindow & window)
{
	if (m_display)
	{
		visualizeRadius(window);
	}
	int i = 0;
	for (Dart* d : darts)
	{
		if (d->isCollided())
		{
			//Deletes the data that is the cause of a collision
			//should this check whether the balloon is dead
			//Well Dart should == nullptr and as such should destroy itself
			d->getTarget()->changeHealth(1);
			Dart* pTemp = d;
			darts.erase(darts.begin() + i);
			delete pTemp;
		}
		if (d->getTarget() == nullptr)
		{
			darts.erase(darts.begin() + i);
		}
		i++;
		d->moveTowards(delta);
		window.draw(*d);
		std::chrono::milliseconds t_CurTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
		if ((t_CurTime.count() - d->getTimeCreated().count()) > 1000)
		{
			Dart* pTemp = d;
			darts.erase(darts.begin() + i);
			delete pTemp;
		}
	}
	this->Render(window);
	//window.draw(this->m_Object);
}

void Tower::addBalloonToList(Balloon& balloon)
{
	m_BalloonsInRange.push_back(&balloon);
}

Tower::Tower(sf::Vector2f pos, float xSize, float ySize,std::string filePath)
	:SpriteManager(filePath, pos, sf::Vector2f(xSize,ySize))
{
	m_display = false;
	b_xSize = xSize; b_ySize = ySize;
	this->setOrigin(xSize / 2, ySize / 2);
	this->setPosition(pos);
	m_lastThrownDart = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
}
//Checks using distance formula which is totally no correct
//However gets an expected result
bool Tower::isInRadius(sf::Vector2f otherPos, Balloon& b1)
{
	//Way to many )
	//Math is now correct plus adds 10 pixels to make it seem more visually appealing
	float distance = sqrt(abs((pow((this->getPosition().x - (b1.getPos().x)), 2) + (pow(((this->getPosition().y) - (b1.getPos().y + 25)), 2)))));
	//std::cout << "Distance: " << distance << std::endl;
	if (distance < default_Radius)
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
	sf::CircleShape radiusVisual(default_Radius, 30);
	radiusVisual.setOrigin(sf::Vector2f(default_Radius - b_xSize/2, default_Radius - b_ySize/2));
	radiusVisual.setPosition(this->getPosition().x, (this->getPosition().y));
	radiusVisual.setFillColor(sf::Color(0, 100, 0,25));
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
		newDart->setTimeCreated(t_CurTime);
		darts.push_back(newDart);
		m_lastThrownDart = t_CurTime;
	}
}
