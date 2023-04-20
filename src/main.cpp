#include<SFML/Graphics.hpp>
//#include<SFML/OpenGL.hpp>
#include<iostream>
#include<fstream>

#include"includes/Ballon.hpp"
#include"includes/Tower.hpp"

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

	Balloon b1(1, sf::Vector2f(0, 500));
	Tower t1(sf::Vector2f(250, 250), 100, 100);
	std::vector<sf::Vector2f> coords;
	coords.push_back(sf::Vector2f(1000, 500));
	coords.push_back(sf::Vector2f(500, 1000));
	int coordIndex = 0;
	sf::Clock clock;
	float delta = 0;

	while (window.isOpen())
	{
		delta = clock.restart().asSeconds() * 60;
		b1.moveTowards(coords[coordIndex], 1*delta);
		if (MathHelper::MathHelp::isAround(b1.getPos(), coords[coordIndex], 10))
		{
			std::cout << "HERE" << std::endl;
			coordIndex++;
		}
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
		window.draw(t1);
		t1.visualizeRadius(200, window, b1);
		t1.update(delta,window);
		b1.Render(window);
		window.draw(m_sprite);
		window.display();
	}

	return 0;
}