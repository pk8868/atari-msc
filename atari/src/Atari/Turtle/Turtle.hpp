#pragma once
#include "Atari/Canvas/Canvas.hpp"
#include "Atari/Interpreter/Interpreter.hpp"
// pomocnicza struktura do wyœwietlania danych o ¿ó³wiu
struct TurtleData {
	sf::Vector2i currentPosition = sf::Vector2i{ 0, 0 };
	float rotation = 0.f;
	bool penDown = true;
	bool visible = true;

	// czy jest aktywny
	bool active = true;
};

class Turtle {
public:
	Turtle();
	~Turtle();

	void Draw(sf::RenderTarget& window);
	
	bool Run(const Interpreter::ShortInstruction& instruction);
	bool Run(const Interpreter::OneArgInstruction& instruction);

	TurtleData getTurtleData() { return m_data; }
	TurtleData& getTurtleDataRef() { return m_data; }
private:
	sf::Sprite m_turtleSprite;

	// tekstura dla zolwii (updateowana co Draw() zeby zapobiec petli)
	const sf::Texture* textureptr = nullptr;

	TurtleData m_data;	
private:
	void p_move(int amount);
	void p_rotate(float angle);

	// normalizacja wektora tak, aby pozycja 0,0 by³a na œrodku planszy
	sf::Vector2f p_normalizeVector(sf::Vector2f vector);
};