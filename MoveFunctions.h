#pragma once
#include <SFML/Graphics.hpp>
#include "AnalyticGeometry.h"


void moveTo(sf::Shape* shape, sf::Vector2f to, float speed)
{
	sf::Vector2f p = shape->getPosition();
	static auto p0 = p;
    sf::Vector2f N = (to - p0) / Norm2d<float>(to - p0);
	if (IsPointInSegment(p, p0, to)) {
		shape->move(speed * N);
	}	
}