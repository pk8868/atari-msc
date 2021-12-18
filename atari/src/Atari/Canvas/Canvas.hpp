#pragma once
#include <SFML/Graphics.hpp>

class Canvas {
private:
	struct Line {
		sf::Vector2f point_A;
		sf::Vector2f point_B;
		sf::Color color;
	};
public:
	Canvas(sf::Vector2i windowSize);
	~Canvas();

	void DrawOnScreen(sf::RenderWindow& r_window);

	// narysowanie linii
	void Draw(const sf::Vector2f& point_A, const sf::Vector2f& point_B, const sf::Color& color, bool newLine = true);
	void Clear();
	void Update() { p_Texture.display(); }

	void newWindowSize(sf::Vector2u windowSize);

	sf::Image getImage() { return p_Texture.getTexture().copyToImage(); }

	sf::Vector2f getSize() { return sf::Vector2f(p_Texture.getSize()); }

	sf::RenderTarget& getTarget() { return p_Texture; }
private:
	// plansza (tekstura i sprite)
	sf::RenderTexture p_Texture;
	sf::Sprite p_Sprite;

	// rzeczy u¿yteczne przy rysowaniu linii
	sf::CircleShape p_circleShape;

	// lista linii
	std::vector<Line> lines;

private:
	sf::Vector2f p_normalizeVector(sf::Vector2f vector) {
		vector += sf::Vector2f(p_Texture.getSize()) / 2.f;
		return vector;
	}
};