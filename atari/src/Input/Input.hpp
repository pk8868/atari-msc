#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Atari/Atari.hpp"

class Input {
public:
	Input() { r_window = nullptr; }
	Input(sf::RenderWindow* r_window);
	~Input();
	

	// wyrenderowanie okienka, logika przycisku
	void Update(const std::string& errorCodes, Atari& atari);


	bool shouldGet() { return p_Input.shouldReturn; }

	// zwr�cenie warto�ci pola, zmiana flagi shouldReturn na false 
	std::string getString();

	// wyczyszczenie textu w inpucie, wykona si� tylko, gdy interpreter nie zwr�ci b��du
	void clear();
private:
	sf::RenderWindow* r_window;

	struct {
		std::string inputText = "";
		bool shouldReturn = false;
	} p_Input;
};