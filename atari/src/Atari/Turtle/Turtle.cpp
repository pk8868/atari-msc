#include "pch.h"
#include "Turtle.hpp"
#include "Utils/Utils.hpp"

Turtle::Turtle(sf::Texture* texturePtr, Canvas* canvas)
	:r_canvas(canvas)
{
	// ustawienie tekstury, srodka ¿ó³wia i pozycji
	m_turtleSprite.setTexture(*texturePtr);
	m_turtleSprite.setOrigin(sf::Vector2f(texturePtr->getSize() / 2U));
}

Turtle::~Turtle() {
	r_canvas = nullptr;
}

void Turtle::Draw(sf::RenderTarget& window) {
	if (m_data.visible) {
		// ustawienie pozycji ¿ó³wia przy kazdym renderowaniu ze wzgledu na zmiane rozmiaru okna
		m_turtleSprite.setPosition(p_normalizeVector(sf::Vector2f(m_data.currentPosition)));
		
		window.draw(m_turtleSprite);
	}
}

void Turtle::ExecuteInstructionSet(const Instruction& instructionSet) {
	if (!m_data.active)
		return;

	// powtórzenie zestawu
	switch (instructionSet.instruction) {
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
		p_move(-instructionSet.arg[0]);
		break;
		// ruch do ty³u
	case Instructions::BK:
		p_move(instructionSet.arg[0]);
		break;

		// obrót w prawo
	case Instructions::RT:
		p_rotate((float)instructionSet.arg[0]);
		break;

		// obrót w lewo
	case Instructions::LT:
		p_rotate((float)-instructionSet.arg[0]);
		break;
	}

	// ustawienie rotacji ¿ó³wia
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
