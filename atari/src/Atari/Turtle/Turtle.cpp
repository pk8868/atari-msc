#include "pch.h"
#include "Turtle.hpp"
#include "Utils/Utils.hpp"
#include "Atari/Atari.hpp"

Turtle::Turtle() {

}

Turtle::~Turtle() {
	;
}

void Turtle::Draw(sf::RenderTarget& window) {
	if (!textureptr) {
		textureptr = Atari::Get().getTexture();

		m_turtleSprite.setTexture(*textureptr);
		m_turtleSprite.setOrigin((sf::Vector2f)textureptr->getSize() / 2.f);
	}

	if (m_data.visible) {
		// ustawienie pozycji ¿ó³wia przy kazdym renderowaniu ze wzgledu na zmiane rozmiaru okna
		m_turtleSprite.setPosition(p_normalizeVector(sf::Vector2f(m_data.currentPosition)));
		m_turtleSprite.setRotation(m_data.rotation);
		window.draw(m_turtleSprite);
	}
}

bool Turtle::Run(const Interpreter::ShortInstruction& instruction) {
	if (!m_data.active)
		return true;
	
	switch (instruction.type) {
	case Interpreter::Instruction::Type::HT:
		m_data.visible = false;
		break;
	case Interpreter::Instruction::Type::ST:
		m_data.visible = true;
		break;

	case Interpreter::Instruction::Type::PU:
		m_data.penDown = false;
		break;
	case Interpreter::Instruction::Type::PD:
		m_data.penDown = true;
		break;
	}


	return true;
}

bool Turtle::Run(const Interpreter::OneArgInstruction& instruction) {
	switch (instruction.type) {
	case Interpreter::Instruction::Type::LT:
		p_rotate(-instruction.value);
		break;
	case Interpreter::Instruction::Type::RT:
		p_rotate(instruction.value);
		break;

	case Interpreter::Instruction::Type::FD:
		p_move(-instruction.value);
		break;
	case Interpreter::Instruction::Type::BK:
		p_move(instruction.value);
		break;
	}


	return true;
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
		Canvas::Get().Draw(sf::Vector2f(old_pos),
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
	vector += Canvas::Get().getSize() / 2.f;
	return vector;
}
