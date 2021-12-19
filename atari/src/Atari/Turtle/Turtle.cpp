#include "pch.h"
#include "Turtle.hpp"
#include "Utils/Utils.hpp"

Turtle::Turtle(sf::Texture* texturePtr, Canvas* canvas)
	:r_canvas(canvas)
{
	// ustawienie tekstury, srodka ¿ó³wia i pozycji
	m_turtleSprite.setTexture(*texturePtr);
	m_turtleSprite.setOrigin(sf::Vector2f(texturePtr->getSize() / 2U));
	m_turtleSprite.setPosition(p_normalizeVector(sf::Vector2f(0.f, 0.f)));
}

Turtle::~Turtle() {
	r_canvas = nullptr;
}

void Turtle::Draw(sf::RenderTarget& window) {
	if (m_data.visible) {
		m_turtleSprite.setPosition(p_normalizeVector(sf::Vector2f(m_data.currentPosition)));
		window.draw(m_turtleSprite);
	}
}

void Turtle::ExecuteInstructionSet(InstructionSet& instructionSet) {
	// powtórzenie zestawu
	for (int j = 0; j < instructionSet.set_data.repeat; j++) {

		// przejœcie przez wszystkie instrukcje w zestawie
		for (int i = 0; i < instructionSet.size(); i++) {
			switch (instructionSet[i].instruction) {
				// ukrycie ¿ó³wia
			case Instructions::HT:
				m_data.visible = false;
				break;

				// pokazanie ¿ó³wia
			case Instructions::ST:
				m_data.visible = true;
				break;

				// podniesienie pisaka
			case Instructions::PU:
				m_data.penDown = false;
				break;

				// opuœæ pisak
			case Instructions::PD:
				m_data.penDown = true;
				break;


				// ========== ruch ¿ó³wia ============
				// ruch do przodu
			case Instructions::FD:
				p_move(-instructionSet[i].arg);
				break;
				// ruch do ty³u
			case Instructions::BK:
				p_move(instructionSet[i].arg);
				break;

				// obrót w prawo
			case Instructions::RT:
				p_rotate((float)instructionSet[i].arg);
				break;

				// obrót w lewo
			case Instructions::LT:
				p_rotate((float)-instructionSet[i].arg);
				break;

			case Instructions::CS:
				r_canvas->Clear();
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
		r_canvas->Draw(sf::Vector2f(old_pos),
					   sf::Vector2f(m_data.currentPosition),
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
	vector += r_canvas->getSize() / 2.f;
	return vector;
}
