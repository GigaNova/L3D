#pragma once
#include <SFML/Graphics/Color.hpp>
#include <cstdlib>

static sf::Color getRandomColor()
{
	return sf::Color(rand() % 255, rand() % 255, rand() % 255);
}
