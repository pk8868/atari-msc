#pragma once
#include <SFML/Graphics.hpp>

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

};

class Turtle {
public:
	Turtle();
	~Turtle();

	void Draw();
	
	void ExecuteInstruction();

	// liczba ¿ó³wii
	static int m_turtleCount;
private:
	// tekstura wspólna dla wszystkich instancji ¿ó³wii
	static sf::Texture* m_turtleTexture;

	sf::Sprite m_turtleSprite;

};