#ifndef UI_HPP
#define UI_HPP

#include <SFML\Graphics.hpp>
#include <fstream>
#include <iostream>	

//This is an abstract class that will be used for each UI element
//like the tower placement menu, the pause Menu, the replay
//menu, the main menu
class UI_Element
{
public:
	UI_Element(void) {}

	virtual void update(sf::RenderWindow& window) = 0;
	virtual void handleMouseClick(sf::RenderWindow& window) = 0;


private:

};



#endif UI_HPP