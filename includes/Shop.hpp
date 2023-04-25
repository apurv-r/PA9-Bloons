#ifndef	SHOP_HEADER_CLASS
#define SHOP_HEADER_CLASS

#include<iostream>
#include<vector>

#include"includes/Game.hpp"

class Shop
{
public:
	Shop(Game& game, sf::Font* font);

	void whatToBuy();

	void update(sf::RenderWindow& window);

	void handleMouseInput(sf::RenderWindow& window);

	void RenderShop(sf::RenderWindow& window);

	void giveBackValue();

private:
	
	sf::RectangleShape m_TowerToPlace;

	sf::RectangleShape menuBase;
	sf::RectangleShape monkeyButton;

	Game* m_game;

	sf::Texture m_texture;

	sf::Font* m_font;
	sf::Text m_MoneyText;

	bool activeItem;
	std::chrono::milliseconds m_lastPurchase;
};

#endif