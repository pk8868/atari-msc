#include "pch.h"
#include "Canvas.hpp"
#include "Utils/Utils.hpp"
#include "App/App.hpp"

Canvas::Canvas() {
	p_circleShape.setRadius(1.5f);
	p_circleShape.setOrigin({ 1.5f, 1.5f });

	// y * 0.8f, zeby nie stworzylo sie pod UI
	if (!p_Texture.create(App::Get().m_appSettings.windowSize.x, int(App::Get().m_appSettings.windowSize.y * 0.8f),
		sf::ContextSettings(0, 0, 16)))
		throw std::runtime_error("Couldn't create canvas");

	Clear();
}

Canvas::~Canvas() {
	;
}

Canvas& Canvas::Get()
{
	static Canvas m_Canvas;
	return m_Canvas;
}

void Canvas::DrawOnScreen(sf::RenderWindow& r_window) {
	p_Sprite.setTexture(p_Texture.getTexture());
	r_window.draw(p_Sprite);
}

void Canvas::Draw(const sf::Vector2f& point_A, const sf::Vector2f& point_B, const sf::Color& color, bool newLine) {	
	// stworzenie grubej linii od a do b
	{
		sf::VertexArray temp_buffer(sf::PrimitiveType::Lines);


		temp_buffer.append(sf::Vertex(p_normalizeVector(point_A), color));
		temp_buffer.append(sf::Vertex(p_normalizeVector(point_B), color));

		p_Texture.draw(temp_buffer);

		if (newLine)
			lines.emplace_back(point_A, point_B, color);
	}

	// stworzenie dwóch kó³ na punkcie A i B
	{
		// ustawienie koloru
		p_circleShape.setFillColor(color);

		// zaokr¹glenie punktu A
		p_circleShape.setPosition(p_normalizeVector(point_A));
		p_Texture.draw(p_circleShape);

		// zaokr¹glenie punktu B
		p_circleShape.setPosition(p_normalizeVector(point_B));
		p_Texture.draw(p_circleShape);
		
	}

	p_Texture.display();
}

void Canvas::Clear() {
	lines.clear();
	lines.reserve(20);

	p_Texture.clear(sf::Color::White);
	p_Texture.display();
}

void Canvas::newWindowSize(sf::Vector2u windowSize) {
	// zapisanie starej planszy
	sf::Texture temp_oldCanvas = p_Texture.getTexture();
	sf::Sprite temp_oldCanvasSprite(temp_oldCanvas);
	temp_oldCanvasSprite.setOrigin(sf::Vector2f(temp_oldCanvas.getSize() / 2U));

	

	// stworzenie nowego canvasa
	if (!p_Texture.create(windowSize.x, int(windowSize.y * 0.8f), sf::ContextSettings(0, 0, 16)))
		throw std::runtime_error("Couldn't create canvas");

	// wycentrowanie starego canvasa
	temp_oldCanvasSprite.setPosition(sf::Vector2f(p_Texture.getSize() / 2U));

	// wyrenderowanie starego canvasa na oknie
	p_Texture.clear(sf::Color::White);

	// narysowanie linii od nowa
	for (int i = 0; i < lines.size(); i++)
		Draw(lines[i].point_A, lines[i].point_B, lines[i].color, false);


	p_Texture.display();

}

