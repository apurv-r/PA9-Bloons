#pragma once
#include"includes/Tower.hpp"
#include"includes/Boomerang.hpp"
#include<string>
#define monkeySpritePath "Resources/testingImage.jpg"

class BoomerangMonkey :public Tower
{
public:
	BoomerangMonkey(sf::Vector2f pos, float boomerang_radius, int power = default_DartPower, int delay = default_Delay, int radius = default_Radius)
		:Tower(pos, m_Xsize, m_YSize, monkeySpritePath)
	{
		this->m_boomerang_radius = boomerang_radius;
		this->m_delay = delay;
		this->m_dartPower = power;
		this->m_Radius = (float)radius;
		this->m_TimesinceDartThrown = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
		m_lastThrownDart = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	};

	virtual bool isInRadius(sf::Vector2f otherPos, Balloon& b1);

	//Draws the radius 
	virtual void visualizeRadius(sf::RenderWindow& window);

	virtual void update(float delta, sf::RenderWindow& window);

	void throwDart();

protected:
	std::vector<Boomerang*> boomerangs;
private:
	std::chrono::milliseconds m_TimesinceDartThrown;
	const std::string m_SpritePath = "Resources/testingImage.jpg";
	const float m_Xsize = 100;
	float const m_YSize = 100;
	float m_boomerang_radius = 150;
};