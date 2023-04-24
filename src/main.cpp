#include<SFML/Graphics.hpp>
//#include<SFML/OpenGL.hpp>
#include<iostream>
#include<fstream>

#include"includes/Game.hpp"

int main()
{
	int windowX = 1000;
	int windowY = 1000;
	float direction = .1;

	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "SFML works!");
	
	//Textures Work now
	std::string s1 = "Resources/testingImage.jpg";
	sf::Texture tex1;
	tex1.loadFromFile(s1.c_str());
	sf::Sprite m_sprite;
	m_sprite.setPosition(800, 800);
	m_sprite.setTexture(tex1);
	Game game(window, sf::Vector2f(-100, 500));

	int coordIndex = 0;
	sf::Clock clock;
	float delta = 0;

	while (window.isOpen())
	{
		while (game.getLives() > 0)
		{
			delta = clock.restart().asSeconds() * 60;
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			//Closes the program.
			//Makes it easy on me
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
				return 0;
			}
			window.clear();
			//Issue this gets run infinitly so needs to be changed
			game.runGame(delta);
			window.draw(m_sprite);
			window.display();
		}
	}

	return 0;
}