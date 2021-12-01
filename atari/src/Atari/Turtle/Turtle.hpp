#pragma once
#include <SFML/Graphics.hpp>
#include "Atari/Interpreter/CodeStructures.hpp"
#include "Atari/Canvas/Canvas.hpp"



// pomocnicza struktura do wyœwietlania danych o ¿ó³wiu
struct TurtleData {
	sf::Vector2i currentPosition = sf::Vector2i{ 0, 0 };
	float rotation = 0.f;
	bool penDown = true;
	bool visible = true;
};

class Turtle {
public:
	Turtle() { ; }
	Turtle(sf::Texture* texturePtr, Canvas* canvas);
	~Turtle();

	void Draw(sf::RenderWindow& window);
	
	void ExecuteInstructionSet(InstructionSet& instructionSet);

	TurtleData getTurtleData() { return m_data; }
private:
	// tekstura wspólna dla wszystkich instancji ¿ó³wii
	sf::Sprite m_turtleSprite;

	TurtleData m_data;

private:
	Canvas* r_canvas = nullptr;
	
private:
	void p_move(int amount);
	void p_rotate(float angle);

	// normalizacja wektora tak, aby pozycja 0,0 by³a na œrodku planszy
	sf::Vector2f p_normalizeVector(sf::Vector2f vector);
};