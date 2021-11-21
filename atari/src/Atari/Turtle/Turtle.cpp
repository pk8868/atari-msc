#include "pch.h"
#include "Turtle.hpp"

Turtle::Turtle(sf::Vector2i canvasSize, sf::Texture* texturePtr) 
	:m_canvasSize(sf::Vector2f(canvasSize)), m_turtleTexture(texturePtr)
{
	m_turtleSprite.setTexture(*m_turtleTexture);
	m_turtleSprite.setOrigin(sf::Vector2f(m_turtleTexture->getSize() / 2u));
}

Turtle::~Turtle() {

}

void Turtle::Draw(sf::RenderWindow& window) {
	if (m_data.visible) {
		m_turtleSprite.setPosition(m_data.currentPosition + m_canvasSize / 2.f);
		window.draw(m_turtleSprite);
	}
}

void Turtle::ExecuteInstructionSet(InstructionSet& instructionSet) {

}
