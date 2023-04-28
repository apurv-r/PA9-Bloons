#include "includes/Shop.hpp"

Shop::Shop(Game& game, sf::Font *font)
{ 

	m_font = font;
	m_MoneyText.setFont(*m_font);
	m_MoneyText.setFillColor(sf::Color::Magenta);
	m_game = &game;
	activeItem = false; 
	m_lastPurchase = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	//Sets up buttons and shop UI
	this->menuBase = sf::RectangleShape(sf::Vector2f(300, 2000));
	this->menuBase.setPosition(1700, 0);
	this->menuBase.setFillColor(sf::Color(205, 133, 63));

	this->monkeyButton = sf::RectangleShape(sf::Vector2f(100, 200));
	this->monkeyButton.setPosition(1750, 50);
	this->monkeyButton.setFillColor(sf::Color(32, 178, 170));

};


void Shop::whatToBuy()
{
}

void Shop::update(sf::RenderWindow &window)
{
	std::string l_msg = "Total Money: " + std::to_string(m_game->getMoney());
	this->m_MoneyText.setString(l_msg);

	giveBackValue();

	if (activeItem)
	{
		this->m_TowerToPlace.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
	}

	RenderShop(window);
}

void Shop::handleMouseInput(sf::RenderWindow& window)
{
	if (activeItem)
	{
		//Will check if Active
		const sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(window));
		bool isContained = false;
		for (sf::RectangleShape marker : this->m_game->getMarkers())
		{
			//Have to check all 4 corners
			if (marker.getGlobalBounds().contains(pos+sf::Vector2f(50,50))|| marker.getGlobalBounds().contains(pos + sf::Vector2f(-50, -50))|| marker.getGlobalBounds().contains(pos + sf::Vector2f(50, -50))|| marker.getGlobalBounds().contains(pos + sf::Vector2f(-50, 50)))
			{
				std::cout << "Cannot Place here" << std::endl;
				isContained = true;
			}
		}
		if (!isContained)
		{
			this->m_game->spawnTower(pos);
			activeItem = false;
		}
	}
	else
	{
		//Struct for the buttons?
		if (monkeyButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
		{
			//Add logic as if can you buy
			std::chrono::milliseconds curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
		//	std::cout << "Time dif: " << (curTime.count() - m_lastPurchase.count()) << std::endl;
			if (m_game->getMoney() >= 100 && (curTime.count() - m_lastPurchase.count()) > 1000)
			{
				this->activeItem = true;
				this->m_texture.loadFromFile("Resources/testingImage.jpg");
				this->m_TowerToPlace.setTexture(&this->m_texture);
				//Breaks every so often I dont know why
				this->m_TowerToPlace.setOrigin(50, 50);
				this->m_TowerToPlace.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
				this->m_TowerToPlace.setSize(sf::Vector2f(100, 100));
				m_lastPurchase = curTime;
				m_game->subtractMoney(100);
			}
			//Still here just incase something odd comes up
			/*else if (!((curTime.count() - m_lastPurchase.count()) > 1000) && m_game->getMoney() >= 100)
			{
				this->activeItem = true;
				this->m_texture.loadFromFile("Resources/testingImage.jpg");
				this->m_TowerToPlace.setTexture(&this->m_texture);
				this->m_TowerToPlace.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
				this->m_TowerToPlace.setSize(sf::Vector2f(100, 100));
				std::cout << "Pressed to Quickly Try again in a bit" << std::endl;
			}*/
			else
			{
				std::cout << "insuficient funds" << std::endl;
			}
		}
	}
}

void Shop::RenderShop(sf::RenderWindow& window)
{
	if (activeItem)
		window.draw(m_TowerToPlace);

	window.draw(m_MoneyText);
	window.draw(this->menuBase);
	window.draw(this->monkeyButton);
}

void Shop::giveBackValue()
{
	if (this->activeItem)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			this->m_game->addMoney(100);
			this->activeItem = false;
		}
	}
}
