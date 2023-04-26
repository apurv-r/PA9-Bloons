#include"includes/Tower.hpp"
#include<string>
#define monkeySpritePath "Resources/testingImage.jpg"

class Monkey :public Tower
{
public:
	Monkey(sf::Vector2f pos, int power = default_DartPower, int delay = default_Delay, int radius = default_Radius)
		:Tower(pos, m_Xsize, m_YSize, monkeySpritePath)
	{
		this->m_delay = delay;
		this->m_dartPower = power;
		this->m_Radius = (float)radius;
		m_lastThrownDart = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	};

	virtual bool isInRadius(sf::Vector2f otherPos, Balloon& b1);
	
	//Draws the radius 
	virtual void visualizeRadius(sf::RenderWindow& window);

	virtual void update(float delta, sf::RenderWindow& window);

private:
	const std::string m_SpritePath = "Resources/testingImage.jpg";
	const float m_Xsize = 100, const m_YSize = 100;
};