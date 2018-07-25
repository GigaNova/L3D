#pragma once
#include <SFML/System/Clock.hpp>
#include <ostream>
#include <iostream>

class DeltaTime
{
public:
	static void update();

	static double deltaTime;
	static sf::Clock* deltaClock;
};
