#ifndef	SHOP_HEADER_CLASS
#define SHOP_HEADER_CLASS

#include<iostream>
#include<vector>

#include"includes/Game.hpp"
#include "includes/UI.hpp"

class Shop : public UI_Element
{
public:
	Shop(Game& game, sf::Font* font, sf::RenderWindow& window);

	void whatToBuy();

	void update(sf::RenderWindow& window) override;

	void handleMouseClick(sf::RenderWindow& window) override;

	void RenderShop(sf::RenderWindow& window);

	void giveBackValue();

private:
	bool MonkeyMenuOn;
	sf::RectangleShape MonkeyMenu;
	sf::Font font;
	sf::Text mHealthText, mBananasText;
	sf::CircleShape openMenuButton;
	sf::RectangleShape closeMenuButton;

	sf::RectangleShape m_TowerToPlace;
	sf::RectangleShape monkeyButton;
	Game* m_game;
	sf::Texture m_texture;
	sf::Font* m_font;
	sf::Text m_MoneyText;
	bool activeItem;
	std::chrono::milliseconds m_lastPurchase;
};

#endif