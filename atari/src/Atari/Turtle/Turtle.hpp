#pragma once
#include <SFML/Graphics.hpp>

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

};

class Turtle {
public:
	Turtle();
	~Turtle();

	void Draw();
	
	void ExecuteInstruction();

	// liczba ��wii
	static int m_turtleCount;
private:
	// tekstura wsp�lna dla wszystkich instancji ��wii
	static sf::Texture* m_turtleTexture;

	sf::Sprite m_turtleSprite;

};