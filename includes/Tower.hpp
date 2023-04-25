#ifndef TOWER_CLASS_h
#define TOWER_CLASS_h

#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<chrono>
#include<ratio>
#include<vector>

#include"includes/Dart.hpp"

/// <summary>
/// implement Upgrades?
/// Multi ballon detection
/// Map creation just for fun
/// Tower placement
/// Tower polymorphism
/// </summary>

class Tower : public sf::RectangleShape
{
public:
	Tower(sf::Vector2f pos, float xSize, float ySize, float radius);

	//Checks using distance formula which is totally no correct
	//However gets an expected result
	bool isInRadius(sf::Vector2f otherPos, Balloon& b1);

	//Draws the radius 
	void visualizeRadius(sf::RenderWindow  & window);

	void update(float delta, sf::RenderWindow  & window);

	void addBalloonToList(Balloon& balloon);

	bool getDisplayBool() { return m_display; };

	void setDisplayBool(bool newDisplay) { m_display = newDisplay; };

private:

	int default_Delay = 800;
	int delay;
	int default_DartPower = 1;
	int dartPower;
	float default_Radius;
	float m_Radius;

	bool m_display;


	void throwDart(Balloon& target);

	sf::Vector2f m_pos;


	std::vector<Dart*> darts;
	std::chrono::milliseconds m_lastThrownDart;

	std::vector<Balloon*> m_BalloonsInRange;
};

#endif