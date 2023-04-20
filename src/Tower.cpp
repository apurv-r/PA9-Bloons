#include "includes/Tower.hpp"

//Check this code most likely inaccurate
void Tower::update(float delta, sf::RenderWindow& window)
{
	for (int i = 0; i < darts.size(); i++)
	{
		if (darts[i]->isCollided())
		{
			std::cout << "Collision" << std::endl;
			//Need a way to delete the dart
			//A simple delete does not work
		}
	}
	for (Dart* d : darts)
	{
		d->moveTowards(delta);
		window.draw(*d);
	}
}

/// <summary>
/// Throw Dart
/// TODO: Dart should be thrown every so often not every 
/// frame this causes massive lag
/// </summary>
/// <param name="target"></param>
void Tower::throwDart(Balloon& target)
{
	Dart* newDart = new Dart(50, 50, 5, target);
	darts.push_back(newDart);
}
