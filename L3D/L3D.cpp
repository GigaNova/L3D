#include <SFML/Graphics.hpp>
#include "LWindow.h"
#include "LMath.h"
#include "LCamera.h"
#include "LTime.h"
#include "LOBJLoader.h"
#include "LRandom.h"

int main()
{
	srand(time(NULL));

    LWindow window(1024, 1024);
	LCamera camera(1024, 1024, 0.1f, 1000.0f, 90.0f);
	window.setCamera(&camera);

	mesh teapot = LOBJLoader::loadOBJ("teapot");
	sf::Color color = getRandomColor();
    while (window.isOpen())
    {
		DeltaTime::update();

		window.pollEvents(new sf::Event());
		window.start();
		window.drawMesh(teapot, color);
		window.end();
    }

    return 0;
}
