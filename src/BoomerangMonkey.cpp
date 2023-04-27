#include "includes/BoomerangMonkey.hpp"

bool BoomerangMonkey::isInRadius(sf::Vector2f otherPos, Balloon& b1)
{
	//Way to many )
	//Math is now correct plus adds 10 pixels to make it seem more visually appealing
	float distance = sqrt(abs((pow(((this->m_Object.getPosition().x) - (b1.getPos().x)), 2) + (pow((this->m_Object.getPosition().y) - (b1.getPos().y), 2)))));
	//std::cout << "Distance: " << distance << std::endl;
	if (distance < m_Radius)
	{
		addBalloonToList(b1);
		this->throwDart();
		return true;
	}
	return false;

}

void BoomerangMonkey::visualizeRadius(sf::RenderWindow& window)
{
	sf::CircleShape radiusVisual(m_Radius, 30);
	radiusVisual.setOrigin(sf::Vector2f(m_Radius - m_Xsize / 2, m_Radius - m_YSize / 2));
	radiusVisual.setPosition(this->m_Object.getPosition().x, (this->m_Object.getPosition().y));
	radiusVisual.setFillColor(sf::Color(0, 100, 0));
	window.draw(radiusVisual);
}

void BoomerangMonkey::update(float delta, sf::RenderWindow& window)
{
	Balloon* tempBallon = nullptr;
	std::cout << boomerangs.size() << std::endl;
	if (m_display)
	{
		visualizeRadius(window);
	}
	//this->Render(window);
	for (Boomerang* d : boomerangs)
	{
		d->moveTowards(delta);
		std::cout << d->getPosition().x << "   " << d->getPosition().y << std::endl;
		window.draw(*d);
	}
	for (int i = 0; i < boomerangs.size(); i++)
	{
		if (boomerangs[i]->isCollided(m_BalloonsInRange, tempBallon))
		{
			tempBallon->changeHealth(m_dartPower);
		}
		std::chrono::milliseconds t_CurTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
		if (((t_CurTime.count() - this->m_TimesinceDartThrown.count()) > 18000) /*&& boomerangs[i]->getGlobalBounds().intersects(this->m_Object.getGlobalBounds())*/) {
			boomerangs.erase(boomerangs.begin() + i);
		}
	}
	//window.draw(this->m_Object);
}

void BoomerangMonkey::throwDart() {
	//Gets the current time since epoch inwhich high_resolution_clocks epoch not sure what the actual epoch value is
	//Could be 01/01/1970 not that big of an issue
	std::chrono::milliseconds t_CurTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	//t_CurTime is going to be larger than m_lastThrownDart.
	if ((t_CurTime.count() - m_lastThrownDart.count()) > 800)
	{
		Boomerang* newDart = new Boomerang(50, 50, 5, this->m_boomerang_radius, this->m_Object.getPosition());
		boomerangs.push_back(newDart);
		m_lastThrownDart = t_CurTime;
	}
}