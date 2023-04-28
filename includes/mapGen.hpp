#ifndef MAPGEN_HEADER
#define MAPGEN_HEADER
#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <chrono>
#include <vector>
#include <sstream>

class mapGen
{
public:
	mapGen();

	void run(sf::RenderWindow & window);

	std::vector<sf::Vector2f> loadMapRandom(std::vector<std::string> files);
	std::vector<sf::Vector2f> loadMapSpecific(std::string files);

private:

	typedef enum dir {
		NONE, LEFT, RIGHT, UP, DOWN
	} Direction;

	std::string generateRandomString(int length);

	sf::Texture upArrow, downArrow, rightArrow, leftArrow;
	sf::Font font;
};

#endif