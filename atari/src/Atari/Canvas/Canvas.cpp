#include "pch.h"
#include "Canvas.hpp"
#include "Utils/Utils.hpp"

Canvas::Canvas(sf::Vector2i windowSize) {
	p_circleShape.setRadius(1.5f);
	p_circleShape.setOrigin({ 1.5f, 1.5f });


	if (!p_Texture.create(windowSize.x, windowSize.y, sf::ContextSettings(0, 0, 16)))
		throw std::runtime_error("Couldn't create canvas");

	Clear();
}

Canvas::~Canvas() {

}

void Canvas::DrawOnScreen(sf::RenderWindow& r_window) {
	p_Sprite.setTexture(p_Texture.getTexture());
	r_window.draw(p_Sprite);
}

void Canvas::Draw(const sf::Vector2f& point_A, const sf::Vector2f& point_B, const sf::Color& color) {	
	// stworzenie grubej linii od a do b
	{
		sf::VertexArray temp_buffer(sf::PrimitiveType::Lines);


		temp_buffer.append(sf::Vertex({ point_A.x, point_A.y }, color));
		

		temp_buffer.append(sf::Vertex({ point_B.x, point_B.y }, color));

		p_Texture.draw(temp_buffer);
	}

	// stworzenie dwóch kó³ na punkcie A i B
	{
		// ustawienie koloru
		p_circleShape.setFillColor(color);

		// zaokr¹glenie punktu A
		p_circleShape.setPosition(point_A);
		p_Texture.draw(p_circleShape);

		// zaokr¹glenie punktu B
		p_circleShape.setPosition(point_B);
		p_Texture.draw(p_circleShape);
		
	}

	p_Texture.display();
}

void Canvas::Clear() {
	p_Texture.clear(sf::Color::White);
	p_Texture.display();
}
