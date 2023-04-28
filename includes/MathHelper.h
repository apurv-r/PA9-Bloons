#ifndef MATHHELP_H
#define MATHHELP_H

#include<cmath>
#include<iostream>
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
		static bool isAround(const sf::Vector2f& mainPos, const sf::Vector2f& targetPos, float offset)
		{
			if (mainPos.x - offset <= targetPos.x && mainPos.x + offset >= targetPos.x && mainPos.y - offset <= targetPos.y && mainPos.y + offset >= targetPos.y)
			{
				return true;
			}
			return false;
		}

		static float dot(const sf::Vector2f& v1, const sf::Vector2f& v2)
		{
			return ((v1.x * v2.x) + (v1.y * v2.y));
		}

		//finds next place to go in circle
		static sf::Vector2f circleMath(const sf::Vector2f& v, float radius) {
			sf::Vector2f b = sf::Vector2f((radius * sin(v.x * 3.14 / 180)), (radius * cos(v.y * 3.14 / 180)));
			return b;
		}

		MathHelp() {};
		void runTest()
		{
			testDot();
			testABS();
			testisAround();
			testNormalize();
		}
		void testDot()
		{
			sf::Vector2f v1(2, 2);
			sf::Vector2f v2(3, 3);
			float result = dot(v1, v2);
			if (result == 12)
			{
				std::cout << "Passed dot product Testing" << std::endl;
			}
			else
			{
				std::cout << "Failed Dot product Testing. Result was " << result << " It should have been 6" << std::endl;
			}
		};
		void testABS()
		{
			sf::Vector2f test(-5, 9);
			sf::Vector2f expectedResult(5, 9);
			sf::Vector2f result = abs(test);

			if (expectedResult == result)
			{
				std::cout << "Passed abs product Testing" << std::endl;
			}
			else
			{
				std::cout << "Failed abs product Testing. Result was " << result.x<<"  "<<result.y << " It should have been (5,9)" << std::endl;
			}
		};
		void testisAround() 
		{
			sf::Vector2f pos(100, 100);
			sf::Vector2f target(105, 105);
			float offset = 10;
			if (isAround(pos, target, offset))
			{
				std::cout << "Passed isAround product Testing" << std::endl;
			}
			else
			{
				std::cout << "Failed isAround product Testing. Result was false It should have been true" << std::endl;
			}
		};
		void testNormalize() 
		{
			sf::Vector2f vector(10, 10);
			sf::Vector2f expectedResult(10 / sqrt(200), 10 / sqrt(200));
			sf::Vector2f result = normalize(vector);
			if(result == expectedResult)
			{
				std::cout << "Passed normalize product Testing" << std::endl;
			}
			else
			{
				std::cout << "Failed normalzie product Testing. Result was" << result.x<<"  "<<result.y<< "  It should have been true" << std::endl;
			}
		};

	};
}

#endif // !MATHHELP_H