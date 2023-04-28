#include "includes/Game.hpp"

Game::Game(sf::RenderWindow& window, sf::Vector2f balloonSpawnLoc, sf::Font font, mapGen& gen) :m_Window(&window), m_BalloonSpawnLoc(balloonSpawnLoc)
{
	srand(time(NULL));
	//__cplusplus has to be enabled by the /Zc:__cplusplus
	//command line directive.
	//Just gives the version of complier. I.e. the value for the iso version
	//After more research _MSVC_LANG also works but is not universal
#if __cplusplus == 201703
	//Needs to be run in c++17 to have access to std::filesystem::directory_iterator
	std::string path = "CustomMaps/";
	std::vector<std::string> paths;
	//Code from by https://stackoverflow.com/a/612176
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		paths.push_back(entry.path().string());
		std::cout << entry.path() << std::endl;
	}
	m_coords = gen.loadMapRandom(paths);
#else 
	//Map must be declared
	m_coords = gen.loadMap("CustomMaps/map-eSmVf.txt");
#endif
	loadInvsibleMarkers();
	m_LevelDisplay.setFont(font);
	m_LevelDisplay.setFillColor(sf::Color::Red);
	this->m_LevelDisplay.setString("Null");
	m_LevelDisplay.setPosition(sf::Vector2f(1500, 0));
	m_totalMoney = 100;
	Monkey* m1 = new Monkey(sf::Vector2f(300, 250), 2,800,300);
	m_TowerObjects.push_back(m1);
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
	if (m_level / 10 >= m_Levels.size() - 1) {}
	else
	{
		m_levelInstance = m_level / 10;
	}

	if (m_balloonsSpawned == m_Levels[m_levelInstance]->maxBalloons)
	{
		m_level++;
		m_balloonsSpawned = 0;
		m_totalMoney += m_Levels[m_levelInstance]->maxBalloons;
	}
	std::chrono::milliseconds t_CurTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	//std::cout << (t_CurTime.count() - m_LastBalloonSpawn.count()) << std::endl;
	if ((t_CurTime.count() - m_LastBalloonSpawn.count()) > m_Levels[m_levelInstance]->delay)
	{
		m_BalloonObjects.push_back(new Balloon(rand() % m_Levels[m_levelInstance]->maxLevel + 1	, m_BalloonSpawnLoc, m_coords));
		m_LastBalloonSpawn = t_CurTime;
		this->m_balloonsSpawned++;
	}
	for (sf::RectangleShape rect : m_invisbleMarkers)
	{
		m_Window->draw(rect);
	}
	
	//Should not be dependent on the balloons being spawned
	for (Tower* l_tower : m_TowerObjects)
	{
		l_tower->update(delta, *m_Window);
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
			m_totalMoney += m_BalloonObjects.at(l_balloonLoc)->getInitHealth();
			Balloon* pTemp = m_BalloonObjects.at(l_balloonLoc);
			m_BalloonObjects.erase(m_BalloonObjects.begin() + l_balloonLoc);
			delete pTemp;
		}

		l_balloonLoc++;
	}

	if (m_level / 10 >= m_Levels.size()-1) {}
	else
	{
		m_levelInstance = m_level / 10;
	}

	//renderText(*m_Window,l_msg);
	//Bad line but why?
	
	//(*m_Window).draw(m_livesDisplay);
	
}

void Game::spawnTower(sf::Vector2f const & pos)
{
	Monkey* t_tower = new Monkey(pos, 2, 500);
	m_TowerObjects.push_back(t_tower);
}

void Game::runThroughTowers()
{
	for (Tower* t : m_TowerObjects)
	{
		if (t->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*m_Window))))
		{
			t->setDisplayBool(true);
		}
		else
		{
			t->setDisplayBool(false);
		}
	}
}

void Game::renderText(sf::RenderWindow& window,std::string msg)
{
//	window.draw(m_livesDisplay);
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

void Game::loadInvsibleMarkers()
{
	for (sf::Vector2f v : m_coords)
	{
		//Size is bigger because of how the coords are generated in the map code
		//Between the first and second and the last two coords a gap exists that isn't
		//spanned by 100 pixels its larger so the size of the track has to increase in response
		sf::RectangleShape* t_Shape = new sf::RectangleShape(sf::Vector2f(200, 120));
		t_Shape->setOrigin(sf::Vector2f(85, 60));
		t_Shape->setPosition(v);
		t_Shape->setFillColor(sf::Color(181,101,29));
		m_invisbleMarkers.push_back(*t_Shape);
	}

}
