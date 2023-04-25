#include<SFML/Graphics.hpp>

class SpriteManager
{
public:
	SpriteManager(std::string imageFilePath, sf::Vector2f pos)
	:m_Pos(pos)
	{
		m_Texture.loadFromFile(imageFilePath);
		m_Object  = sf::CircleShape(50, 30);
		m_Object.setPosition(m_Pos);
		m_Object.setTexture(&m_Texture);
	};

	void Render(sf::RenderWindow &window);

	sf::Vector2f getPos() { m_Pos = (sf::Vector2f(m_Object.getPosition().x + m_Object.getRadius(), m_Object.getPosition().y + m_Object.getRadius())); return m_Pos; };
	//sf::Vector2f getPos() { m_Pos = (sf::Vector2f(m_Sprite.getPosition().x , m_Sprite.getPosition().y)); return m_Pos; };

	void changeTexture(sf::Texture newTexture) { m_Texture = newTexture; };
	sf::CircleShape m_Object;
private:
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
	sf::Vector2f m_Pos;

};