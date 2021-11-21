#pragma once
#include <SFML/Graphics.hpp>

class Canvas {
public:
	Canvas() { ; }
	Canvas(sf::Vector2i windowSize);
	~Canvas();

	void DrawOnScreen(sf::RenderWindow& r_window);

	void Draw(const sf::Vector2f& point_A, const sf::Vector2f& point_B, const sf::Color& color);
	void Clear();

	
private:
	// plansza (tekstura i sprite)
	sf::RenderTexture p_Texture;
	sf::Sprite p_Sprite;

	// rzeczy u¿yteczne przy rysowaniu linii
	sf::CircleShape p_circleShape;

};