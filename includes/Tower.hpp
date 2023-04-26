#ifndef TOWER_CLASS_h
#define TOWER_CLASS_h

#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<chrono>
#include<vector>

#include"includes/Dart.hpp"

/// <summary>
/// implement Upgrades?
/// Multi ballon detection
/// Map creation just for fun
/// Tower placement
/// Tower polymorphism
/// </summary>

class Tower : public SpriteManager
{
public:
	Tower(sf::Vector2f pos, float xSize, float ySize, std::string filePath);

	//Checks using distance formula which is totally no correct
	//However gets an expected result
	virtual bool isInRadius(sf::Vector2f otherPos, Balloon& b1);

	//Draws the radius 
	virtual void visualizeRadius(sf::RenderWindow  & window);

	virtual void update(float delta, sf::RenderWindow  & window);

	void addBalloonToList(Balloon& balloon);

	bool getDisplayBool() { return m_display; };

	void setDisplayBool(bool newDisplay) { m_display = newDisplay; };

	//Public so that they can be used as default values in function declarations
	static const int default_Delay = 800;
	static const int default_DartPower = 1;
	static const int default_Radius = 250.0f;

protected:

	int b_xSize, b_ySize;
	int m_delay;
	int m_dartPower;
	float m_Radius;

	bool m_display;

	void throwDart(Balloon& target);

	std::vector<Dart*> darts;
	std::chrono::milliseconds m_lastThrownDart;

	std::vector<Balloon*> m_BalloonsInRange;
};

#endif