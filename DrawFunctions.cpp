// DrawFunctions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <windows.h> // SLEEP 

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 800

bool inMandelbrotSet(float cx, float cy);
sf::Vector2f functionValue(float x, float y, float cx, float cy);

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Mandelbr0");


	//std::cout << inMandelbrotSet(-1.5, 0.1) << std::endl;

	sf::RectangleShape pixel(sf::Vector2f(1.f, 1.f));

	// Mouse coordinates
	int x = 0;
	int y = 0;

	float nIterations = 800;

	float xLower = -2.f;
	float xUpper = 1.f;
	float yLower = -1.f;
	float yUpper = 1.f;

	xLower = -0.066f;
	xUpper = -0.049f;
	yLower = -0.8495f;
	yUpper = -0.807f;



	// Creating the points.
	// Move this to a callable function in order to make a fractal zoomer!

	std::vector<sf::Vector2f> mandelbrotSet;

	for (float xIteration = 0; xIteration < nIterations; ++xIteration) {
		for (float yIteration = 0; yIteration < nIterations; ++yIteration) {

			//float cx = -2 + xIteration * 3 / nIterations;
			//float cy = -1 + yIteration * 2 / nIterations;

			float cx = xLower + xIteration * abs(xLower - xUpper) / nIterations;
			float cy = yLower + yIteration * abs(yLower - yUpper) / nIterations;

			if (inMandelbrotSet(cx, cy)) mandelbrotSet.push_back(sf::Vector2f(xIteration, yIteration));

		}
	}



	float redValue = 130.f;
	float greenValue = 30.f;
	float blueValue = 255.f;


	float xWorld = 0.f;
	float yWorld = 0.f;

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				x = sf::Mouse::getPosition(window).x;
				y = sf::Mouse::getPosition(window).y;
				std::cout << x << " " << y << std::endl;

				xWorld = xLower + (x / 800.f) * abs(xLower - xUpper);
				yWorld = yLower + (y / 800.f) * abs(yLower - yUpper);

				std::cout << xWorld << " " << yWorld << std::endl;
				break;
			}
			//else if ()
			else break;
		}



		window.clear();

		// Figure out somehow to change the colors smoothly...
		// Try: move drawing command to the inMandelbrotSet function

		for (auto& point : mandelbrotSet) {
			pixel.setFillColor(sf::Color(redValue, greenValue, blueValue));
			pixel.setPosition(point.x, point.y);
			window.draw(pixel);
		}

		window.display();

	}

	return 0;
}

bool inMandelbrotSet(float cx, float cy) {
	float x = 0;
	float y = 0;

	int iterationIndex = 0;
	int iterationMax = 100;

	while (iterationIndex < iterationMax) {
		sf::Vector2f z = functionValue(x, y, cx, cy);

		if (z.x > 2.f || z.y > 2.f) return false;
		x = z.x;
		y = z.y;
		iterationIndex++;
	}
	return true;
}


sf::Vector2f functionValue(float x, float y, float cx, float cy) {
	float xValue = x*x - y*y + cx;
	float yValue = 2 * x*y + cy;

	sf::Vector2f returnVector(xValue, yValue);

	return(returnVector);
}