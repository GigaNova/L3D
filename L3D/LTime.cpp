#include "LTime.h"
sf::Clock* DeltaTime::deltaClock = new sf::Clock();
double DeltaTime::deltaTime = 0.0;

void DeltaTime::update()
{
	sf::Time time = deltaClock->restart();
	deltaTime = time.asSeconds();
}
