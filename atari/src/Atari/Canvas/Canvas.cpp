#include "pch.h"
#include "Canvas.hpp"
#include "Utils/Utils.hpp"
#include "App/App.hpp"

static sf::Color background = sf::Color(225, 225, 225);

Canvas::Canvas() {
	p_circleShape.setRadius(1.5f);
	p_circleShape.setOrigin({ 1.5f, 1.5f });
	// y * 0.8f, zeby nie stworzylo sie pod UI
	if (!p_Texture.create(App::Get().m_appSettings.windowSize.x, int(App::Get().m_appSettings.windowSize.y * 0.8f)))
		ErrorLog::Log(Error{ Error::Critical, "Couldn't create canvas" });

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
		sf::RectangleShape shape;
		sf::Vector2f x{ 2.f, util::getDistance(point_A, point_B) };
		shape.setSize(x);
		shape.setOrigin({1.f, x.y});
		shape.setFillColor(sf::Color::Black);
		shape.setRotation(util::getAngle(point_A, point_B));
		shape.setPosition(p_normalizeVector(point_A));
		p_Texture.draw(shape);

		if (newLine)
			lines.emplace_back(point_A, point_B, color);
	}

	p_Texture.display();
}

void Canvas::Clear() {
	lines.clear();
	lines.reserve(20);

	p_Texture.clear(background);
	p_Texture.display();
}

void Canvas::newWindowSize(sf::Vector2u windowSize) {
	// stworzenie nowego canvasa
	if (!p_Texture.create(windowSize.x, int(windowSize.y * 0.8f)))
		ErrorLog::Log(Error{ Error::Critical, "Couldn't create canvas" });
	p_Texture.setView(p_Texture.getDefaultView());
	p_Texture.clear(background);

	// narysowanie linii od nowa
	for (int i = 0; i < lines.size(); i++)
		Draw(lines[i].point_A, lines[i].point_B, lines[i].color, false);


	p_Texture.display();

}

