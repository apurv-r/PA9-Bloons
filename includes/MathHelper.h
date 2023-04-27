#ifndef MATHHELP_H
#define MATHHELP_H

#include<cmath>
#include<SFML/System/Vector2.hpp>

namespace MathHelper
{
	class MathHelp
	{
	public:
		//Normalizes the vector used in the moveTowards calculations
		//i.e. needs to reduce the vector to less than 1
		static sf::Vector2f normalize(const sf::Vector2f& v)
		{
			float length = sqrt((v.x * v.x) + (v.y * v.y));
			return sf::Vector2f((v.x / length), (v.y / length));
		}
		//Simple checker used again in the moveTowards Calcualtion
		static sf::Vector2f abs(const sf::Vector2f& v)
		{
			sf::Vector2f result = v;
			if (v.x < 0)
				result.x *= -1;
			if (v.y < 0)
				result.y *= -1;

			return result;
		}
		//because it may not be at the same exact position a isAround function is 
		//needed the offest is adjustable.
		static bool isAround(const sf::Vector2f& mainPos, const sf::Vector2f &targetPos, float offset)
		{
			if (mainPos.x - offset <= targetPos.x && mainPos.x + offset >= targetPos.x && mainPos.y - offset <= targetPos.y && mainPos.y + offset >= targetPos.y)
			{
				return true;
			}
			return false;
		}
		//finds next place to go in circle
		static sf::Vector2f circleMath(const sf::Vector2f& v, float radius){
		
			return sf::Vector2f((radius + radius * sin(v.x)), (radius + radius * sin(v.y)));
		}
	};
}

#endif // !MATHHELP_H