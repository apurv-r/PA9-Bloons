#include"includes/SpriteManager.hpp"

void SpriteManager::Render(sf::RenderWindow& window)
{
	window.draw(*this);
}