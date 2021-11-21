#pragma once
#include <SFML/Graphics.hpp>

// z pliku interpreter
class InstructionSet;


// instrukcje, które wykonuje ¿ó³w
enum class TurtleInstructions : short {
	None = 0xffff,

	// instrukcje nie wymagaj¹ce argumentów
	// ukryj ¿ó³wia
	HT = 0x2,
	// poka¿ ¿ó³wia
	ST = 0x4,
	// podnieœ 
	PU = 0x6,
	// 
	PD = 0x8,

	// instrukcje wymagaj¹ce argumentu
	// obrót w prawo
	RT = 0x1,
	// obrót w lewo
	LT = 0x3,
	// do przodu
	FD = 0x5,
	// do ty³u
	BK = 0x7
};

// pomocnicza struktura do wyœwietlania danych o ¿ó³wiu
struct TurtleData {
	sf::Vector2f currentPosition = sf::Vector2f(0.f, 0.f);
	float rotation = 0.f;
	bool penDown = true;
	bool visible = true;
};

class Turtle {
public:
	Turtle() { ; }
	Turtle(sf::Vector2i canvasSize, sf::Texture* texturePtr);
	~Turtle();

	void Draw(sf::RenderWindow& window);
	
	void ExecuteInstructionSet(InstructionSet& instructionSet);

	TurtleData& getTurtleData() { return m_data; }
private:
	// tekstura wspólna dla wszystkich instancji ¿ó³wii
	sf::Texture* m_turtleTexture = nullptr;

	sf::Sprite m_turtleSprite;

	TurtleData m_data;

private:
	sf::Vector2f m_canvasSize;
};