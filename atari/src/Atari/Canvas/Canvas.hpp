#pragma once
#include <SFML/Graphics.hpp>

class Canvas {
public:
	Canvas();
	~Canvas();

	void DrawOnScreen(sf::RenderWindow& r_window);

	void Draw(const sf::Vector2f& point_A, const sf::Vector2f& point_B, const sf::Color& color);
	void Clear();

	
private:
	sf::RenderTexture p_Texture;
};