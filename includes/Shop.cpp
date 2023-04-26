#include "Shop.hpp"

Shop::Shop(Game& game, sf::Font *font, sf::RenderWindow &window)
{ 

	m_font = font;
	m_MoneyText.setFont(*m_font);
	m_MoneyText.setFillColor(sf::Color::Magenta);
	m_game = &game;
	activeItem = false; 
	m_lastPurchase = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	//Sets up buttons and shop UI

	/*this->monkeyButton = sf::RectangleShape(sf::Vector2f(100, 200));
	this->monkeyButton.setPosition(750, 50);
	this->monkeyButton.setFillColor(sf::Color(32, 178, 170));*/

	monkeyButton.setOrigin(0, 0);
	monkeyButton.setFillColor(sf::Color::Cyan);
	monkeyButton.setSize(sf::Vector2f(150, 100));
	monkeyButton.setPosition(sf::Vector2f(window.getSize().x - 225, 200));

	MonkeyMenu.setPosition(sf::Vector2f(window.getSize().x, 0));
	MonkeyMenu.setSize(sf::Vector2f(300, window.getSize().y));
	MonkeyMenu.setFillColor(sf::Color::Blue);


	mHealthText.setFont(*font);
	mHealthText.setFillColor(sf::Color::Red);
	mHealthText.setCharacterSize(24);
	mHealthText.setPosition(10, 20);

	mBananasText.setFont(*font);
	mBananasText.setFillColor(sf::Color::Red);
	mBananasText.setCharacterSize(24);
	mBananasText.setPosition(10, 40);

	openMenuButton.setRadius(40);
	openMenuButton.setOrigin(0, 0);
	openMenuButton.setPosition(sf::Vector2f(window.getSize().x - 100, 25));
	openMenuButton.setFillColor(sf::Color::Yellow);

	closeMenuButton.setOrigin(0, 0);
	closeMenuButton.setFillColor(sf::Color::Yellow);
	closeMenuButton.setSize(sf::Vector2f(150, 100));
	closeMenuButton.setPosition(sf::Vector2f(window.getSize().x - 225, window.getSize().y - 200));

};


void Shop::whatToBuy()
{
}

void Shop::update(sf::RenderWindow &window)
{
	/*std::string l_msg = "Total Money: " + std::to_string(m_game->getMoney());
	this->m_MoneyText.setString(l_msg);

	giveBackValue();

	if (activeItem)
	{
		this->m_TowerToPlace.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
	}

	RenderShop(window);*/


	if (MonkeyMenuOn == false && MonkeyMenu.getPosition().x != window.getSize().x)
	{
		window.draw(MonkeyMenu);
		MonkeyMenu.move(20, 0);
	}
	else if (!MonkeyMenuOn)
	{
		//display an open menu option
		window.draw(openMenuButton);
	}
	else if (MonkeyMenuOn == true && MonkeyMenu.getPosition().x != window.getSize().x - 300)
	{
		window.draw(MonkeyMenu);
		MonkeyMenu.move(-20, 0);
	}
	else if (MonkeyMenuOn)
	{
		window.draw(MonkeyMenu);
		window.draw(monkeyButton);
		window.draw(closeMenuButton);
	}

	if (activeItem)
	{
		window.draw(m_TowerToPlace);
	}

	giveBackValue();

	if (activeItem)
	{
		this->m_TowerToPlace.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
	}

	//display score and whatnot
	mHealthText.setString("Lives: " + std::to_string(m_game->getLives()));
	mBananasText.setString("Bananas: " + std::to_string(m_game->getMoney()));

	window.draw(mHealthText);
	window.draw(mBananasText);
}

void Shop::handleMouseClick(sf::RenderWindow& window)
{
	//opening Menu
	if (MonkeyMenuOn == false
		&& openMenuButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
	{
		MonkeyMenuOn = true;
	}
	else if (closeMenuButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
	{
		
		MonkeyMenuOn = false;
		
	}

	//Placing tower stuff
	if (activeItem)
	{
		//Will check if Active
		const sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(window));
		this->m_game->spawnTower(pos);
		activeItem = false;
	}
	else
	{
		//Struct for the buttons?
		if (monkeyButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
		{
			//Add logic as if can you buy
			std::chrono::milliseconds curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
			std::cout << "Time dif: " << (curTime.count() - m_lastPurchase.count()) << std::endl;
			if (m_game->getMoney() >= 100 && (curTime.count() - m_lastPurchase.count()) > 1000)
			{
				MonkeyMenuOn = false;
				this->activeItem = true;
				this->m_texture.loadFromFile("Resources/testingImage.jpg");
				this->m_TowerToPlace.setTexture(&this->m_texture);
				this->m_TowerToPlace.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
				this->m_TowerToPlace.setSize(sf::Vector2f(100, 100));
				m_lastPurchase = curTime;
				m_game->subtractMoney(100);
			}
			else if (!((curTime.count() - m_lastPurchase.count()) > 1000) && m_game->getMoney() >= 100)
			{
				this->activeItem = true;
				this->m_texture.loadFromFile("Resources/testingImage.jpg");
				this->m_TowerToPlace.setTexture(&this->m_texture);
				this->m_TowerToPlace.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
				this->m_TowerToPlace.setSize(sf::Vector2f(100, 100));
				std::cout << "Pressed to Quickly Try again in a bit" << std::endl;
			}
			else
			{
				std::cout << "insuficient funds" << std::endl;
			}
		}
	}
}

//void Shop::RenderShop(sf::RenderWindow& window)
//{
//	if (activeItem)
//	{
//		window.draw(m_TowerToPlace);
//	}
//
//	window.draw(m_MoneyText);
//	window.draw(this->menuBase);
//	window.draw(this->monkeyButton);
//}

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
