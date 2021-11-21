#pragma once
#include <SFML/Graphics.hpp>

// z pliku interpreter
class InstructionSet;


// instrukcje, kt�re wykonuje ��w
enum class TurtleInstructions : short {
	None = 0xffff,

	// instrukcje nie wymagaj�ce argument�w
	// ukryj ��wia
	HT = 0x2,
	// poka� ��wia
	ST = 0x4,
	// podnie� 
	PU = 0x6,
	// 
	PD = 0x8,

	// instrukcje wymagaj�ce argumentu
	// obr�t w prawo
	RT = 0x1,
	// obr�t w lewo
	LT = 0x3,
	// do przodu
	FD = 0x5,
	// do ty�u
	BK = 0x7
};

// pomocnicza struktura do wy�wietlania danych o ��wiu
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
	// tekstura wsp�lna dla wszystkich instancji ��wii
	sf::Texture* m_turtleTexture = nullptr;

	sf::Sprite m_turtleSprite;

	TurtleData m_data;

private:
	sf::Vector2f m_canvasSize;
};