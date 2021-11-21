#include "pch.h"
#include "Canvas.hpp"

Canvas::Canvas(sf::Vector2i windowSize) {
	p_circleShape.setRadius(1.f);
	p_circleShape.setOrigin({ 1.f, 1.f });
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
		sf::VertexArray temp_buffer(sf::PrimitiveType::Quads, 4);
		// lewy dolny
		temp_buffer.append(sf::Vertex({ point_A.x - 1.f, point_A.y }, color));
		// prawy dolny
		temp_buffer.append(sf::Vertex({ point_A.x + 1.f, point_A.y }, color));

		// prawy górny
		temp_buffer.append(sf::Vertex({ point_B.x + 1.f, point_B.y }, color));
		// lewy górny
		temp_buffer.append(sf::Vertex({ point_B.x - 1.f, point_B.y }, color));

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
	p_Texture.clear();
	p_Texture.display();
}
