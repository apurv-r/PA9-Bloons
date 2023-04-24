#include "includes/Game.hpp"

Game::Game(sf::RenderWindow& window, sf::Vector2f balloonSpawnLoc) :m_Window(&window), m_BalloonSpawnLoc(balloonSpawnLoc)
{
	srand(time(NULL));
	Tower* t1 = new Tower(sf::Vector2f(250, 350), 100, 100, 250);
	m_TowerObjects.push_back(t1);
	m_level = 0, m_lives = 200;
	m_LastBalloonSpawn = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	readBalloonFile("Resources/Balloon.txt");
};

Game::~Game()
{
	m_Levels.clear();
	m_TowerObjects.clear();
	m_BalloonObjects.clear();
}

void Game::runGame(float delta)
{
	int l_balloonsSpawned = 0;
	int levelInstance = m_level / 10;

	std::chrono::milliseconds t_CurTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	std::cout << (t_CurTime.count() - m_LastBalloonSpawn.count()) << std::endl;
	if ((t_CurTime.count() - m_LastBalloonSpawn.count()) > m_Levels[levelInstance]->delay)
	{
		m_BalloonObjects.push_back(new Balloon(rand() % m_Levels[levelInstance]->maxLevel, m_BalloonSpawnLoc));
		m_LastBalloonSpawn = t_CurTime;
	}
	
	int l_balloonLoc = 0;
	for (Balloon* l_balloon : m_BalloonObjects)
	{
		//Better to go first because it can be removed if not valid
		if (l_balloon->getHealth() > 0)
		{
			l_balloon->update(delta, *m_Window);
			for (Tower* l_tower : m_TowerObjects)
			{
				l_tower->isInRadius(l_balloon->getPos(), *l_balloon);
			}
		}
		else
		{
			m_BalloonObjects.erase(m_BalloonObjects.begin() + l_balloonLoc);
		}

		l_balloonLoc++;
	}
	//Should not be dependent on the balloons being spawned
	for (Tower* l_tower : m_TowerObjects)
	{
		l_tower->update(delta, *m_Window);
	}

	if (m_level / 10 >= m_Levels.size()) {}
	else
	{
		levelInstance = m_level / 10;
	}
	
}

void Game::readBalloonFile(std::string filePath)
{
	std::ifstream input;

	std::string newString;

	input.open(filePath.c_str());
	//Second check just in case
	if (!input.is_open())
		return;

	std::string line;
	std::string data[3];
	while (!input.eof())
	{
		std::getline(input, line);
		int end = 0;
		int start = 0;
		for (int i = 0; i < 3; i++)
		{
			end = line.find(",", start);
			data[i] = line.substr(start, end - start);
			start = end + 1;
		}
		Level* tLevel = new Level;
		tLevel->maxLevel = atoi(data[0].c_str());
		tLevel->maxBalloons = atoi(data[1].c_str());
		tLevel->delay= atof(data[2].c_str());
		m_Levels.push_back(tLevel);
	}
}
