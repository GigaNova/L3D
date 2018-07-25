#include "LWindow.h"
#include "LTime.h"

LWindow::LWindow(int _width, int _height)
{
	pInnerWindow = new sf::RenderWindow(sf::VideoMode(_width, _height), MAIN_TITLE);

	pRenderTexture = new sf::Texture();
	pRenderTexture->create(_width, _height);

	pImage = new sf::Image();
	pImage->create(_width, _height);

	width = _width;
	height = _height;

	fTheta = 0.0f;
	wireFrameMode = true;
}

LWindow::~LWindow()
{
}

void LWindow::start()
{
	pInnerWindow->clear();

	for (auto x = 0; x < width; ++x)
	{
		for (auto y = 0; y < height; ++y)
		{
			pImage->setPixel(x, y, sf::Color::Black);
		}
	}
}

bool LWindow::isOpen()
{
	return pInnerWindow->isOpen();
}

void LWindow::pollEvents(sf::Event * _pEvent)
{
	while (pInnerWindow->pollEvent(*_pEvent))
	{
		if (_pEvent->type == sf::Event::Closed)
		{
			pInnerWindow->close();
		}
		else if(_pEvent->type == sf::Event::KeyPressed)
		{
			switch (_pEvent->key.code)
			{
			case sf::Keyboard::W:
				moveCamera(1.0f, 0.0f, 0.0f, 0.0f);
				break;
			case sf::Keyboard::A:
				moveCamera(0.0f, 0.0f, 0.0f, 1.0f);
				break;
			case sf::Keyboard::S:
				moveCamera(0.0f, 0.0f, 1.0f, 0.0f);
				break;
			case sf::Keyboard::D:
				moveCamera(0.0f, 1.0f, 0.0f, 0.0f);
				break;
			case sf::Keyboard::F:
				wireFrameMode = !wireFrameMode;
				break;
			default:
				break;
			}
		}
	}
}

void LWindow::end()
{
	pRenderTexture->loadFromImage(*pImage);

	pInnerWindow->draw(sf::Sprite(*pRenderTexture));
	pInnerWindow->display();
}

void LWindow::drawLine(int _x1, int _y1, int _x2, int _y2, sf::Color _color)
{
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

	if (_x1 == width) _x1 -= 1;
	if (_x2 == width) _x2 -= 1;
	if (_y1 == height) _y1 -= 1;
	if (_y2 == height) _y2 -= 1;

	dx = _x2 - _x1;
	dy = _y2 - _y1;
	dx1 = fabs(dx);
	dy1 = fabs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = _x1;
			y = _y1;
			xe = _x2;
		}
		else
		{
			x = _x2;
			y = _y2;
			xe = _x1;
		}
		if(x > 0 && y > 0 && x < width && y < height)
		{
			pImage->setPixel(x, y, _color);
		}
		for (i = 0; x<xe; i++)
		{
			x = x + 1;
			if (px<0)
			{
				px = px + 2 * dy1;
			}
			else
			{
				if ((dx<0 && dy<0) || (dx>0 && dy>0))
				{
					y = y + 1;
				}
				else
				{
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			if (x > 0 && y > 0 && x < width && y < height)
			{
				pImage->setPixel(x, y, _color);
			}
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = _x1;
			y = _y1;
			ye = _y2;
		}
		else
		{
			x = _x2;
			y = _y2;
			ye = _y1;
		}
		if (x > 0 && y > 0 && x < width && y < height)
		{
			pImage->setPixel(x, y, _color);
		}
		for (i = 0; y<ye; i++)
		{
			y = y + 1;
			if (py <= 0)
			{
				py = py + 2 * dx1;
			}
			else
			{
				if ((dx<0 && dy<0) || (dx>0 && dy>0))
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			if (x > 0 && y > 0 && x < width && y < height)
			{
				pImage->setPixel(x, y, _color);
			}
		}
	}
}

void LWindow::drawVerticalLine(int _x, int _y1, int _y2, sf::Color _color)
{
	if (_y1 < _y2)
	{
		for (auto y = _y1; y <= _y2; ++y)
		{
			pImage->setPixel(_x, y, _color);
		}
	}
	else
	{
		for (auto y = _y1; y >= _y2; --y)
		{
			pImage->setPixel(_x, y, _color);
		}
	}
}

void LWindow::drawTriangle(triangle _triangle, sf::Color _color)
{
	if(!wireFrameMode)
	{
		fillTriangle(_triangle, _color);
	}
	else
	{
		drawLine(_triangle.points[0].x, _triangle.points[0].y, _triangle.points[1].x, _triangle.points[1].y, _color);
		drawLine(_triangle.points[1].x, _triangle.points[1].y, _triangle.points[2].x, _triangle.points[2].y, _color);
		drawLine(_triangle.points[2].x, _triangle.points[2].y, _triangle.points[0].x, _triangle.points[0].y, _color);
	}
}

void LWindow::fillTriangle(triangle _triangle, sf::Color _color)
{
	int maxX = std::max(_triangle.points[0].x, std::max(_triangle.points[1].x, _triangle.points[2].x));
	int minX = std::min(_triangle.points[0].x, std::min(_triangle.points[1].x, _triangle.points[2].x));
	int maxY = std::max(_triangle.points[0].y, std::max(_triangle.points[1].y, _triangle.points[2].y));
	int minY = std::min(_triangle.points[0].y, std::min(_triangle.points[1].y, _triangle.points[2].y));

	vector2 vs1 = { _triangle.points[1].x - _triangle.points[0].x, _triangle.points[1].y - _triangle.points[0].y };
	vector2 vs2 = { _triangle.points[2].x - _triangle.points[0].x, _triangle.points[2].y - _triangle.points[0].y };

	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			vector2 q = { x - _triangle.points[0].x, y - _triangle.points[0].y };

			float s = (float)(cross(q, vs2) / cross(vs1, vs2));
			float t = (float)(cross(vs1, q) / cross(vs1, vs2));

			if ((s >= 0) && (t >= 0) && (s + t <= 1))
			{
				pImage->setPixel(x, y, _color);
			}
		}
	}
}

void LWindow::drawMesh(mesh _mesh, const sf::Color _color)
{
	matrix4 tXrotate, tZRotate, tScale;

	fTheta += 1.0f * (float)DeltaTime::deltaTime;

	tZRotate.m[0][0] = cosf(fTheta);
	tZRotate.m[0][1] = sinf(fTheta);
	tZRotate.m[1][0] = -sinf(fTheta);
	tZRotate.m[1][1] = cosf(fTheta);
	tZRotate.m[2][2] = 1;
	tZRotate.m[3][3] = 1;

	tXrotate.m[0][0] = 1;
	tXrotate.m[1][1] = cosf(fTheta * 0.5f);
	tXrotate.m[1][2] = sinf(fTheta * 0.5f);
	tXrotate.m[2][1] = -sinf(fTheta * 0.5f);
	tXrotate.m[2][2] = cosf(fTheta * 0.5f);
	tXrotate.m[3][3] = 1;

	tScale.m[0][0] = 0.5f;
	tScale.m[1][1] = 0.5f;
	tScale.m[2][2] = 0.5f;
	tScale.m[3][3] = 1;

	for(triangle tri : _mesh.tris)
	{
		triangle tProj, tTrans, tCam, tScaled, tRotZ, tRotZX;

		/*multiplyMatrixVector(tri.points[0], tRotZ.points[0], tZRotate);
		multiplyMatrixVector(tri.points[1], tRotZ.points[1], tZRotate);
		multiplyMatrixVector(tri.points[2], tRotZ.points[2], tZRotate)*/;

		multiplyMatrixVector(tri.points[0], tScaled.points[0], tScale);
		multiplyMatrixVector(tri.points[1], tScaled.points[1], tScale);
		multiplyMatrixVector(tri.points[2], tScaled.points[2], tScale);

		multiplyMatrixVector(tScaled.points[0], tRotZX.points[0], tXrotate);
		multiplyMatrixVector(tScaled.points[1], tRotZX.points[1], tXrotate);
		multiplyMatrixVector(tScaled.points[2], tRotZX.points[2], tXrotate);

		tTrans = tRotZX;
		tTrans.points[0].z = tRotZX.points[0].z + 3.0f;
		tTrans.points[1].z = tRotZX.points[1].z + 3.0f;
		tTrans.points[2].z = tRotZX.points[2].z + 3.0f;

		multiplyMatrixVector(tTrans.points[0], tProj.points[0], matProj);
		multiplyMatrixVector(tTrans.points[1], tProj.points[1], matProj);
		multiplyMatrixVector(tTrans.points[2], tProj.points[2], matProj);

		multiplyMatrixVector(tProj.points[0], tCam.points[0], pCamera->getCameraMatrix());
		multiplyMatrixVector(tProj.points[1], tCam.points[1], pCamera->getCameraMatrix());
		multiplyMatrixVector(tProj.points[2], tCam.points[2], pCamera->getCameraMatrix());

		tCam.points[0].x += 1.0f; tCam.points[0].y += 1.0f;
		tCam.points[1].x += 1.0f; tCam.points[1].y += 1.0f;
		tCam.points[2].x += 1.0f; tCam.points[2].y += 1.0f;

		tCam.points[0].x *= 0.5f * (float)width;
		tCam.points[0].y *= 0.5f * (float)height;
		tCam.points[1].x *= 0.5f * (float)width;
		tCam.points[1].y *= 0.5f * (float)height;
		tCam.points[2].x *= 0.5f * (float)width;
		tCam.points[2].y *= 0.5f * (float)height;

		drawTriangle(tCam, _color);
	}
}

void LWindow::setCamera(LCamera* _pCamera)
{
	pCamera = _pCamera;
	createProjectionMatrix();
}

void LWindow::moveCamera(float up, float right, float down, float left)
{
	if(pCamera)
	{
		vector3 vPos = pCamera->getPos();

		vPos.x += LCamera::CAMERA_SPEED * left;
		vPos.y += LCamera::CAMERA_SPEED * up;

		vPos.x -= LCamera::CAMERA_SPEED * right;
		vPos.y -= LCamera::CAMERA_SPEED * down;

		pCamera->setPos(vPos);
	}
}

int LWindow::getWidth()
{
	return width;
}

int LWindow::getHeight()
{
	return height;
}

void LWindow::createProjectionMatrix()
{
	matProj.m[0][0] = pCamera->getAspectRatio() * pCamera->getFovRad();
	matProj.m[1][1] = pCamera->getFovRad();
	matProj.m[2][2] = pCamera->getFar() / (pCamera->getFar() - pCamera->getNear());
	matProj.m[3][2] = (-pCamera->getFar() * pCamera->getNear()) / (pCamera->getFar() - pCamera->getNear());
	matProj.m[2][3] = 1.0f;
	matProj.m[3][3] = 0.0f;
}
