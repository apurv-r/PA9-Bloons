#include<SFML/Graphics.hpp>
//#include<SFML/OpenGL.hpp>
#include<iostream>
#include<fstream>

#include"includes/Game.hpp"
#include"includes/Shop.hpp"
#include "includes/PauseMenu.hpp"


void l_handleMouseinput(Shop& shop, Game& game, sf::RenderWindow& window);



int main()
{
	int windowX = 2000;
	int windowY = 1000;
	float direction = .1;

	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "SFML works!");
	
	//Textures Work now
	std::string s1 = "Resources/Baloon.png";
	sf::Texture tex1;
	sf::Image testBalloon;
	testBalloon.loadFromFile(s1);
	testBalloon.createMaskFromColor(sf::Color(0, 162, 232));
	tex1.loadFromImage(testBalloon);
	sf::Sprite m_sprite;
	m_sprite.setPosition(800, 800);
	m_sprite.setTexture(tex1);
	sf::Font font;
	font.loadFromFile("Dependencies/Dosis/static/Dosis-Regular.ttf");

	/*
	sf::Text livesText;
	livesText.setFont(font);
	livesText.setCharacterSize(12);
	livesText.setFillColor(sf::Color::Red);
	livesText.setPosition(sf::Vector2f(800, 0));

	sf::Text levelText;
	levelText.setFont(font);
	livesText.setCharacterSize(12);
	levelText.setFillColor(sf::Color::Red);
	levelText.setPosition(sf::Vector2f(800, 0));*/

	/*sf::RectangleShape menu(sf::Vector2f(300, 2000));
	menu.setPosition(1700, 0);
	menu.setFillColor(sf::Color(205, 133, 63));

	sf::RectangleShape monkey(sf::Vector2f(100, 200));
	monkey.setPosition(1750, 50);
	monkey.setFillColor(sf::Color(32,178, 170));*/

	Game game(window, sf::Vector2f(-100, 500),font); 
	Shop shop(game, &font, window);
	PauseMenu pause(window);

	int coordIndex = 0;
	sf::Clock clock;
	float delta = 0;
	window.setFramerateLimit(120);
	bool isPaused = false;

	while (window.isOpen())
	{
		if(game.getLives() > 0)
		{
			delta = clock.restart().asSeconds() * 60;
			
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					return 0;

				case sf::Event::MouseButtonReleased:
					shop.handleMouseClick(window);
					game.runThroughTowers();
					pause.handleMouseClick(window);
					//isPaused = pause.isScreenPaused();
					//std::cout << "Here lol" << std::endl;
					//game.HandleMouseRelease();
				}

					
			}

			//Closes the program.
			//Makes it easy on me
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				window.close();
				return 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				std::cout << "Pause time" << std::endl;
			}

			window.clear();

			if (!pause.isScreenPaused())
			{
				//Issue this gets run infinitly so needs to be changed
				game.runGame(delta);
				shop.update(window);
				pause.update(window);
				//window.draw(m_sprite);
				//window.draw(livesText);
				//window.draw(levelText);
			}
			else
			{
				pause.update(window);
				//window.draw(m_sprite);
				//window.draw(livesText);
				//window.draw(levelText);
			}
			window.display();


		}
	}

	return 0;
}




void l_handleMouseinput(Shop& shop, Game& game, sf::RenderWindow& window)
{
	game.runThroughTowers();
	shop.handleMouseClick(window);
}