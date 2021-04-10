#pragma once
#include <SFML/Graphics.hpp>
#include "math.h"

inline float scalar_prod(sf::Vector2f v_1, sf::Vector2f v_2)
{
	return v_1.x * v_2.x + v_1.y * v_2.y;
}

inline float projection(sf::Vector2f v_1, sf::Vector2f v_2)
{
	return scalar_prod(v_1, v_2) / sqrt(scalar_prod(v_1, v_1));
}

inline sf::Vector2f projection_v(sf::Vector2f v_1, sf::Vector2f v_2)
{
	return v_1 * scalar_prod(v_1, v_2) / scalar_prod(v_1, v_1);
}

inline sf::Vector2f ort(sf::Vector2f v)
{
	return sf::Vector2f(-v.y, v.x);
}

inline float len(sf::Vector2f v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

inline sf::Vector2f normalize(sf::Vector2f v)
{
	if (len(v) != 0) 
		return v / len(v);
	return v;
}

