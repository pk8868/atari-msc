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

	// zwrócenie wartoœci pola, zmiana flagi shouldReturn na false 
	std::string getString();

	// wyczyszczenie textu w inpucie, wykona siê tylko, gdy interpreter nie zwróci b³êdu
	void clear();
private:
	struct {
		std::string inputText = "";
		bool shouldReturn = false;
	} p_Input;
};