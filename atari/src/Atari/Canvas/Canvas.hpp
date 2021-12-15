#pragma once
#include <SFML/Graphics.hpp>

class Canvas {
public:
	Canvas(sf::Vector2i windowSize);
	~Canvas();

	void DrawOnScreen(sf::RenderWindow& r_window);

	// narysowanie linii
	void Draw(const sf::Vector2f& point_A, const sf::Vector2f& point_B, const sf::Color& color);
	void Clear();

	sf::Image getImage() { return p_Texture.getTexture().copyToImage(); }

	sf::Vector2f getSize() { return sf::Vector2f(p_Texture.getSize()); }

private:
	// plansza (tekstura i sprite)
	sf::RenderTexture p_Texture;
	sf::Sprite p_Sprite;

	// rzeczy u¿yteczne przy rysowaniu linii
	sf::CircleShape p_circleShape;

};