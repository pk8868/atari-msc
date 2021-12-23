#pragma once
#include <SFML/System/Vector2.hpp>
#include <math.h>

#define LAUNCH_THREAD(id, ...) id = std::async(std::launch::async, __VA_ARGS__)
#define NEW_THREAD(id, type, ...) std::future<type> id = std::async(std::launch::async, __VA_ARGS__)
#define JOIN_THREAD(id) id.get()


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

	// zapisanie obrazu do pliku
	static void saveToFile(sf::Image image, std::string filename) {
		image.saveToFile(filename);
	}
	
	// wczytanie tekstury
	static bool getTexture(std::string filename, sf::Texture* texture) {
		// jesli nie za³aduje siê tekstura zwróci siê null
		bool done = texture->loadFromFile(filename);
		texture->setSmooth(true);	
		return done;
	}

	// spaghetti do otrzymania godziny
	static std::string getTime() {
		time_t t = time(NULL);

		tm time;
		localtime_s(&time, &t);

		return "[" + std::to_string(1900 + time.tm_year) + "-" +
			(time.tm_mon >= 10 ? std::to_string(time.tm_mon + 1) : "0" + std::to_string(time.tm_mon + 1)) + "-" +
			(time.tm_mday >= 10 ? std::to_string(time.tm_mday) : "0" + std::to_string(time.tm_mday)) + " " +
			std::to_string(time.tm_hour) + ":" +
			(time.tm_min >= 10 ? std::to_string(time.tm_min) : "0" + std::to_string(time.tm_min)) + ":"
			+ (time.tm_sec >= 10 ? std::to_string(time.tm_sec) : "0" + std::to_string(time.tm_sec)) + "]";
	}

	// spaghetti do otrzymania godziny
	static std::string getScreenshotTime() {
		time_t t = time(NULL);

		tm time;
		localtime_s(&time, &t);

		return std::to_string(1900 + time.tm_year) + "_" +
			(time.tm_mon >= 10 ? std::to_string(time.tm_mon + 1) : "0" + std::to_string(time.tm_mon + 1)) + "_" +
			(time.tm_mday >= 10 ? std::to_string(time.tm_mday) : "0" + std::to_string(time.tm_mday)) + "_" +
			std::to_string(time.tm_hour) + "_" +
			(time.tm_min >= 10 ? std::to_string(time.tm_min) : "0" + std::to_string(time.tm_min)) + "_"
			+ (time.tm_sec >= 10 ? std::to_string(time.tm_sec) : "0" + std::to_string(time.tm_sec));
	}

	// godzina, minuta, sekunda
	static std::string getShortTime() {
		time_t t = time(NULL);

		tm time;
		localtime_s(&time, &t);

		return "[" + std::to_string(time.tm_hour) + ":" +
			(time.tm_min >= 10 ? std::to_string(time.tm_min) : "0" + std::to_string(time.tm_min)) + ":"
			+ (time.tm_sec >= 10 ? std::to_string(time.tm_sec) : "0" + std::to_string(time.tm_sec)) + "]";
	}

	// dopisanie do pliku
	static void addToLogFile(const std::string& string) {
		std::ofstream stream("log.txt", std::ios::out | std::ios::app);

		if (stream.good()) {
			stream << getTime() << ": " << string << std::endl;
		}
		else {
			std::cerr << "Couldn't open log.txt\n";
		}

		stream.close();
	}

	template<typename T>
	static std::string vec2ToString(const sf::Vector2<T>& vector, const std::string& separator = ", ") {
		return std::to_string(vector.x) + separator + std::to_string(vector.y);
	}	
}

#ifdef _DEBUG
template<typename T>
static std::ostream& operator<<(std::ostream& stream, const sf::Vector2<T>& vector) {
	stream << vector.x << ", " << vector.y;
	return stream;
}

static std::ostream& operator<<(std::ostream& stream, const sf::Color& color) {
	stream << (int)color.r << ", " << (int)color.g << ", " << (int)color.b << ", " << (int)color.a;
	return stream;
}
#endif