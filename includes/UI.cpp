//#include "UI.hpp"
//
//UI::UI(void)
//{
//	playerHealth = nullptr;
//	playerBananas = nullptr;
//	MonkeyMenuOn = false;
//	placingTower = false;
//	font.loadFromFile("Dependencies/Dosis/static/Dosis-Regular.ttf");
//}
//
//void UI::initializer(sf::RenderWindow& window, int* m_Health, int* m_Bananas)
//{
//	
//
//	towerButton.setOrigin(0, 0);
//	towerButton.setFillColor(sf::Color::Cyan);
//	towerButton.setSize(sf::Vector2f(150, 100));
//	towerButton.setPosition(sf::Vector2f(window.getSize().x - 225, 200));
//
//	towerPlacement.setOrigin(50, 50);
//	towerPlacement.setSize(sf::Vector2f(100, 100));
//	towerPlacement.setFillColor(sf::Color::Magenta);
//}
//
//
//
//void UI::showMonkeyMenu(void) 
//{
//	MonkeyMenuOn = true;
//}
//
//void UI::updateUI(sf::RenderWindow& window)
//{
//	
//	if (MonkeyMenuOn == false && MonkeyMenu.getPosition().x != window.getSize().x)
//	{
//		window.draw(MonkeyMenu);
//		MonkeyMenu.move(20, 0);
//	}
//	else if (!MonkeyMenuOn)
//	{
//		//display an open menu option
//		window.draw(openMenuButton);
//	}
//
//	if (MonkeyMenuOn == true && MonkeyMenu.getPosition().x != window.getSize().x - 300)
//	{
//		window.draw(MonkeyMenu);
//		MonkeyMenu.move(-20, 0);
//	}
//	else if (MonkeyMenuOn)
//	{
//		window.draw(MonkeyMenu);
//		window.draw(towerButton);
//		window.draw(closeMenuButton);
//	}
//
//	if (placingTower && sf::Mouse::isButtonPressed)
//	{
//		towerPlacement.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
//		window.draw(towerPlacement);
//	}
//	//display score and whatnot
//	mHealthText.setString("Lives: " + std::to_string(*playerHealth));
//	mBananasText.setString("Bananas: " + std::to_string(*playerBananas));
//
//	window.draw(mHealthText);
//	window.draw(mBananasText);
//
//}
//
//void UI::checkForMenuOpenClose(sf::RenderWindow &window)
//{
//	if (MonkeyMenuOn == false)
//	{
//		//Check if mouse is in within bounds of menuOnButton
//		if (openMenuButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
//		{
//			MonkeyMenuOn = true;
//		}
//	}
//	else
//	{
//		if (closeMenuButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
//		{
//			MonkeyMenuOn = false;
//		}
//	}
//
//}
//
///*
//This function will check if a player is trying to place a tower, if so, it checks the players money, and if they have enough
//to place a tower, it returns a number cooresponding to which tower to place. Is going to be used in the Game handleMouseClick function
//
//I would've wanted to do this with the game function, but it didn't like that I was trying to include it game.hpp file for some
//reason, so this is why*/
//int UI::checkForTowerPlacement(sf::RenderWindow& window)
//{
//	int result = 0;
//
//	if (MonkeyMenuOn)
//	{
//		if (towerButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
//		{
//			if (*playerBananas >= 50)
//			{
//				placingTower = true;
//				result = 1;
//			}
//			else
//			{
//				std::cout << "insufficient funds" << std::endl;
//			}
//		}
//	}
//
//	return result;
//}
//
//sf::Vector2f UI::getTowerPlacement(void)
//{
//	placingTower = false;
//	return sf::Vector2f(sf::Mouse::getPosition());
//}
