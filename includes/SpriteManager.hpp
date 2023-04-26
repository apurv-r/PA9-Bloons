#include<SFML/Graphics.hpp>

class SpriteManager
{
public:
	SpriteManager(std::string imageFilePath, sf::Vector2f pos)
	:m_Pos(pos)
	{
		m_Texture.loadFromFile(imageFilePath);
		m_Object = sf::Sprite(m_Texture, sf::Rect<int>(sf::Vector2i(pos), sf::Vector2i(100, 100)));
		m_Object.setOrigin(sf::Vector2f(50, 50));
		m_Object.setTexture(m_Texture);
		m_Object.setPosition(m_Pos);
	};

	void Render(sf::RenderWindow &window);

	sf::Vector2f getPos() { m_Pos = (sf::Vector2f(m_Object.getPosition().x, m_Object.getPosition().y )); return m_Pos; };
	//sf::Vector2f getPos() { m_Pos = (sf::Vector2f(m_Sprite.getPosition().x , m_Sprite.getPosition().y)); return m_Pos; };

	void changeTexture(sf::Texture newTexture) { m_Texture = newTexture; };
	sf::Sprite m_Object;
private:
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
	sf::Vector2f m_Pos;

};