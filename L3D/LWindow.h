#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "LCamera.h"

class LWindow
{
public:
	const char* MAIN_TITLE = "L3D";
	LWindow(int _width, int _height);
	~LWindow();

	void start();
	bool isOpen();
	void pollEvents(sf::Event* _pEvent);
	void end();

	void drawLine(int _x1, int _y1, int _x2, int _y2, sf::Color _color);
	void drawVerticalLine(int _x, int _y1, int _y2, sf::Color _color);
	void drawTriangle(triangle _triangle, sf::Color _color);
	void fillTriangle(triangle _triangle, sf::Color _color);
	void drawMesh(mesh _mesh, const sf::Color _color);

	void setCamera(LCamera* _pCamera);
	void moveCamera(float up, float right, float down, float left);

	int getWidth();
	int getHeight();
private:
	bool wireFrameMode;

	int width;
	int height;

	float fTheta;

	sf::RenderWindow* pInnerWindow;
	sf::Texture* pRenderTexture;
	sf::Image* pImage;

	LCamera* pCamera;
	matrix4 matProj;

	void createProjectionMatrix();
};

