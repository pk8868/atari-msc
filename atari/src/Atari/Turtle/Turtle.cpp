#include "pch.h"
#include "Turtle.hpp"
#include "Utils/Utils.hpp"

Turtle::Turtle(sf::Vector2i canvasSize, sf::Texture* texturePtr, Canvas* canvas)
	:m_canvasSize(sf::Vector2f(canvasSize)), m_turtleTexture(texturePtr), r_canvas(canvas)
{
	// ustawienie tekstury, srodka ¿ó³wia i pozycji
	m_turtleSprite.setTexture(*m_turtleTexture);
	m_turtleSprite.setOrigin(sf::Vector2f(m_turtleTexture->getSize() / 2U));
	m_turtleSprite.setPosition(p_normalizeVector(sf::Vector2f(0.f, 0.f)));
}

Turtle::~Turtle() {
	r_canvas = nullptr;
}

void Turtle::Draw(sf::RenderWindow& window) {
	if (m_data.visible)		
		window.draw(m_turtleSprite);
}

void Turtle::ExecuteInstructionSet(InstructionSet& instructionSet) {
	// powtórzenie zestawu
	for (int j = 0; j < instructionSet.set_data.repeat; j++) {

		// przejœcie przez wszystkie instrukcje w zestawie
		for (int i = 0; i < instructionSet.size(); i++) {
			switch (instructionSet[i].instruction) {
				// ukrycie ¿ó³wia
			case TurtleInstructions::HT:
				m_data.visible = false;
				break;

				// pokazanie ¿ó³wia
			case TurtleInstructions::ST:
				m_data.visible = true;
				break;

				// podniesienie pisaka
			case TurtleInstructions::PU:
				m_data.penDown = false;
				break;

				// opuœæ pisak
			case TurtleInstructions::PD:
				m_data.penDown = true;
				break;


				// ========== ruch ¿ó³wia ============
				// ruch do przodu
			case TurtleInstructions::FD:
				p_move(-instructionSet[i].arg);
				break;
				// ruch do ty³u
			case TurtleInstructions::BK:
				p_move(instructionSet[i].arg);
				break;

				// obrót w prawo
			case TurtleInstructions::RT:
				p_rotate((float)instructionSet[i].arg);
				break;

				// obrót w lewo
			case TurtleInstructions::LT:
				p_rotate((float)-instructionSet[i].arg);
				break;
			}
		}

	}

	// ustawienie ¿ó³wia
	m_turtleSprite.setPosition(p_normalizeVector(sf::Vector2f(m_data.currentPosition)));

	m_turtleSprite.setRotation(m_data.rotation);
}

void Turtle::p_move(int amount) {
	// stara pozycja - potrzebna przy rysowaniu linii
	sf::Vector2i old_pos = m_data.currentPosition;

	{ // przesuniêcie ¿ó³wia
		sf::Vector2f temp_move(0.f, (float)amount);
		m_data.currentPosition += sf::Vector2i(util::rotate(temp_move, m_data.rotation));
	}

	// rysowanie na planszy
	if (m_data.penDown)
		r_canvas->Draw(p_normalizeVector(sf::Vector2f(old_pos)),
					   p_normalizeVector(sf::Vector2f(m_data.currentPosition)),
					   sf::Color::Black);

}

void Turtle::p_rotate(float angle) {
	m_data.rotation += angle;

	// sprawdzenie czy rotacja nie wykroczy³a 360 stopni
	while (m_data.rotation >= 360.f)
		m_data.rotation -= 360.f;

	// sprawdzenie czy rotacja nie jest poni¿ej 0 stopni
	while (m_data.rotation < 0.f)
		m_data.rotation += 360.f;

	
}

sf::Vector2f Turtle::p_normalizeVector(sf::Vector2f vector) {
	vector += (m_canvasSize / 2.f);
	return vector;
}
