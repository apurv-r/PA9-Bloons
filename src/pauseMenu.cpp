#include "includes/PauseMenu.hpp"

PauseMenu::PauseMenu(sf::RenderWindow& window)
{
	isPaused = false;
	pauseButton.setRadius(20);
	pauseButton.setOrigin(20, 20);
	pauseButton.setPosition(30, 100);
	pauseButton.setFillColor(sf::Color::Blue);

	pauseBackground.setSize(sf::Vector2f(window.getSize()));
	//pauseBackground.setFillColor(sf::Color::Magenta);
	pauseBackground.setPosition(sf::Vector2f(0, 0));
	//Not working because the drawing of the objects does not happen and is 
	//overwritten on the screen. So technically this works for a single
	//Frame but not for any other frame. This is due to how the rendering 
	//system was set up to begin with, and would technically have to be changed, but
	// has not been.
	pauseBackground.setFillColor(sf::Color(130, 130, 130, 20));


	resumeButton.setSize(sf::Vector2f(150, 100));
	resumeButton.setOrigin(75, 50);
	resumeButton.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	resumeButton.setFillColor(sf::Color::Blue);

	pauseBars[0].setSize(sf::Vector2f(10, 20));
	pauseBars[0].setFillColor(sf::Color::White);
	pauseBars[0].setOrigin(5, 10);
	pauseBars[0].setPosition(pauseButton.getPosition().x - 7, pauseButton.getPosition().y);

	pauseBars[1].setSize(sf::Vector2f(10, 20));
	pauseBars[1].setFillColor(sf::Color::White);
	pauseBars[1].setOrigin(5, 10);
	pauseBars[1].setPosition(pauseButton.getPosition().x + 7, pauseButton.getPosition().y);


}

void PauseMenu::update(sf::RenderWindow& window)
{
	if (!isPaused)
	{
		window.draw(pauseButton);
		window.draw(pauseBars[0]);
		window.draw(pauseBars[1]);
	}
	else
	{
		window.draw(pauseBackground);
		window.draw(resumeButton);
	}
}

void PauseMenu::handleMouseClick(sf::RenderWindow& window)
{
	if (!isPaused && pauseButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
	{
		isPaused = true;

	}
	else if (resumeButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
	{
		isPaused = false;
	}
}

bool PauseMenu::isScreenPaused(void)
{
	return isPaused;
}