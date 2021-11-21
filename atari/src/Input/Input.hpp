#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Input {
public:
	Input();
	~Input();
	

	// wyrenderowanie okienka, logika przycisku
	void Update();


	bool shouldGet() { return p_Input.shouldReturn; }

	// zwr�cenie warto�ci pola, zmiana flagi shouldReturn na false 
	std::string getString();

	// wyczyszczenie textu w inpucie, wykona si� tylko, gdy interpreter nie zwr�ci b��du
	void clear();
private:
	struct {
		std::string inputText = "";
		bool shouldReturn = false;
	} p_Input;
};