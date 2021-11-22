#pragma once
#include <SFML/System/Vector2.hpp>
#include <math.h>

namespace util {
	static float getAngle(const sf::Vector2f& start, const sf::Vector2f& nxt) {
		float ab = (start - nxt).y;
		float ac = sqrt(((start - nxt).x * (start - nxt).x) +
			((start - nxt).y * (start - nxt).y));

		float angle = float(asin(ab / ac) * 57.295827f - 90.f);

		if (start.x < nxt.x) { // adjust angle
			angle *= -1.f;
		}

		return angle;
	} // get angle between two points

	static sf::Vector2f rotate(sf::Vector2f point, float angle) {
		angle *= 0.0174532925f;
		return sf::Vector2f(point.x * cos(angle) - point.y * sin(angle),
			point.x * sin(angle) + point.y * cos(angle));
	} // rotate a vector

	static void saveToFile(sf::Image image, std::string filename) {
		image.saveToFile(filename);
	}
}