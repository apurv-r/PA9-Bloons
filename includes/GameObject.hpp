#include<SFML/Graphics.hpp>
#include<vector>

template <typename T>
class GameObject
{
public:
	GameObject(T object, sf::Vector2f pos)
		:m_Object(object), m_Pos(pos)
	{};

	virtual sf::Vector2f getPos() = 0 {};

	virtual bool render(sf::Window &window) = 0 {};

	virtual T getObject() =0{};

	virtual void setPos(sf::Vector2f pos) = 0 {};
	virtual void setPos(float posX, float posY) = 0 {};

private:
	T m_Object;
	sf::Vector2f m_Pos
};