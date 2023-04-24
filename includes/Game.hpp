#ifndef GAME_HEADER_CLASS
#define GAME_HEADER_CLASS

#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<chrono>
#include<fstream>

#include"includes/Ballon.hpp"
#include"includes/Tower.hpp"

class Game
{
public:
	Game(sf::RenderWindow& window, sf::Vector2f balloonSpawnLoc);

	~Game();

	int getLives() { return m_lives; };

	int whatLevel() { return m_level / 10; };

	void runGame(float delta);

private:
	void readBalloonFile(std::string filePath);

	struct Level
	{
		int maxBalloons = 0;
		int maxLevel = 0;
		float delay = 0.0f;
	};
	
	int m_lives;
	int m_level;
	sf::Vector2f m_BalloonSpawnLoc;

	std::vector<Level*> m_Levels;

	std::chrono::milliseconds m_LastBalloonSpawn;

	sf::RenderWindow* m_Window;
	std::vector<Tower*> m_TowerObjects;
	std::vector<Balloon*> m_BalloonObjects;
};

#endif