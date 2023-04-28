#include<SFML/Graphics.hpp>

class SpriteManager:public sf::RectangleShape
{
public:
	SpriteManager(std::string imageFilePath, sf::Vector2f pos, sf::Vector2f size)
		:m_Pos(pos), sf::RectangleShape(size)
	{
		m_Texture.loadFromFile(imageFilePath);
		this->setTexture(&m_Texture);
		this->setOrigin(sf::Vector2f(size.x/2, size.y/2));
		this->setPosition(m_Pos);
	};

	void Render(sf::RenderWindow &window);

	sf::Vector2f getPos() { m_Pos = (sf::Vector2f(this->getPosition().x, this->getPosition().y )); return m_Pos; };
	//sf::Vector2f getPos() { m_Pos = (sf::Vector2f(m_Sprite.getPosition().x , m_Sprite.getPosition().y)); return m_Pos; };

	void changeTexture(sf::Texture& newTexture) { m_Texture = newTexture; };
	sf::RectangleShape m_Object;
private:
	sf::Texture m_Texture;
	sf::Vector2f m_Pos;

};