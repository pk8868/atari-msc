#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Atari/Atari.hpp"
#include <array>
const int historySize = 5;

class Input {
public:
	Input() { r_window = nullptr; }
	Input(sf::RenderWindow* r_window);
	~Input();
	

	// wyrenderowanie okienka, logika przycisku
	void Update(const std::string& errorCodes);


	bool shouldGet() { return p_Input.shouldReturn; }

	// zwrócenie wartoœci pola, zmiana flagi shouldReturn na false 
	std::string getString();

	// wyczyszczenie textu w inpucie, wykona siê tylko, gdy interpreter nie zwróci b³êdu
	void clear();
private:
	sf::RenderWindow* r_window;

	std::array<std::string, historySize> strings;
	void pushCommand();

	struct {
		std::string inputText = "";
		bool shouldReturn = false;
	} p_Input;
};