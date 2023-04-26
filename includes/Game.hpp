#ifndef GAME_HEADER_CLASS
#define GAME_HEADER_CLASS

#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<chrono>
#include<fstream>

#include"includes/Ballon.hpp"
#include"includes/Monkey.hpp"

class Game
{
public:
	Game(sf::RenderWindow& window, sf::Vector2f balloonSpawnLoc, sf::Font font);

	~Game();

	int getLives() { return m_lives; };

	int whatLevel() { return m_level / 10; };

	void runGame(float delta);

	void spawnTower(sf::Vector2f const & pos);

	int getMoney() { return m_totalMoney; };

	void subtractMoney(int value) { m_totalMoney -= value; };

	void addMoney(int value) { m_totalMoney += value; };

	void runThroughTowers();

	int getLevel() { return this->m_level; };

private:
	void renderText(sf::RenderWindow& window,std::string msg);
	void readBalloonFile(std::string filePath);

	struct Level
	{
		int maxBalloons = 0;
		int maxLevel = 0;
		float delay = 0.0f;
	};
	
	int m_lives;
	int m_level;
	int m_levelInstance;

	int m_balloonsSpawned = 0;

	int m_totalMoney;

	sf::Vector2f m_BalloonSpawnLoc;

	std::vector<Level*> m_Levels;

	std::chrono::milliseconds m_LastBalloonSpawn;

	sf::RenderWindow* m_Window;
	std::vector<Tower*> m_TowerObjects;
	std::vector<Balloon*> m_BalloonObjects;

	sf::Text m_LevelDisplay;
};

#endif