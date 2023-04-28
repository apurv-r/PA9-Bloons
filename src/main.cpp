#include<SFML/Graphics.hpp>
//#include<SFML/OpenGL.hpp>
#include<iostream>
#include<fstream>
#include <string>

#include"includes/Game.hpp"
#include"includes/pauseMenu.hpp"
#include"includes/Shop.hpp"


void l_handleMouseinput(Shop& shop, Game& game, sf::RenderWindow& window);



int main()
{
	int windowX = 2000;
	int windowY = 2000;
	float direction = .1;

	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "SFML works!");
	
	//Textures Work now
	std::string s1 = "Resources/testingImage.jpg";
	sf::Texture tex1;
	tex1.loadFromFile(s1.c_str());
	sf::Sprite m_sprite;
	m_sprite.setPosition(windowX - (windowX/10), windowY - (windowY/10));
	m_sprite.setTexture(tex1);
	
	sf::Font font;
	font.loadFromFile("Dependencies/Dosis/static/Dosis-Regular.ttf");
	sf::Text livesText;
	livesText.setFont(font);
	livesText.setFillColor(sf::Color::Red);
	livesText.setPosition(sf::Vector2f(windowX - (windowX/4), 0));

	sf::Text levelText;
	levelText.setFont(font);
	levelText.setFillColor(sf::Color::Red);
	levelText.setPosition(sf::Vector2f(windowX - (windowX/2), 0));

	/*sf::RectangleShape menu(sf::Vector2f(300, 2000));
	menu.setPosition(1700, 0);
	menu.setFillColor(sf::Color(205, 133, 63));

	sf::RectangleShape monkey(sf::Vector2f(100, 200));
	monkey.setPosition(1750, 50);
	monkey.setFillColor(sf::Color(32,178, 170));*/
	
	//When implementing map generation to the main menu
	//The only thing that needs to happen is that the mapGen
	//run function should be called. Then once that is exited 
	//you can continue.
	mapGen gen;

	Game game(window, sf::Vector2f(-100, 500),font,gen); 
	Shop shop(game, &font);
	PauseMenu pause(window);

	int coordIndex = 0;
	sf::Clock clock;
	float delta = 0;
	window.setFramerateLimit(120);

	while (window.isOpen())
	{
		if (game.getLives() > 0)
		{
			delta = clock.restart().asSeconds() * 60;
			livesText.setString(std::string("Lives:" + std::to_string(game.getLives())));
			levelText.setString(std::string("Level:" + std::to_string(game.getLevel())));

			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseButtonReleased:
					if (!pause.isScreenPaused())
					{
						game.runThroughTowers();
						shop.handleMouseInput(window);
						pause.handleMouseClick(window);
					}
					else
						pause.handleMouseClick(window);
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
			//Bad example code because it breaks but this is essentially what should happen
			//When trying to run the map generator
			/*
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
			{
				gen.run(window);
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				window.clear();
				if (!pause.isScreenPaused())
				{
					game.runGame(delta);
					shop.update(window);
					window.draw(m_sprite);
					window.draw(livesText);
					window.draw(levelText);
				}

				pause.update(window);
				window.display();
			}
			else
			{
				window.clear(sf::Color::Magenta);
				window.display();
			}*/

			//Map Generation looks bad at times because of a issue with how the coords are generated
			//With the last 2 and the first 2 being seperated by 200 pixels instead of 100
			window.clear();
			if (!pause.isScreenPaused())
			{
				game.runGame(delta);
				shop.update(window);
				window.draw(m_sprite);
				window.draw(livesText);
				window.draw(levelText);
			}

			pause.update(window);
			window.display();
		}
	}

	return 0;
}




void l_handleMouseinput(Shop& shop, Game& game, sf::RenderWindow& window)
{
	game.runThroughTowers();
	shop.handleMouseInput(window);
}