#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Input {
public:
	Input();
	~Input();
	
	void Update();


	bool shouldGet() { return p_Input.shouldReturn; }
	std::string getString();
private:
	struct {
		std::string inputText = "";
		bool shouldReturn = false;
	} p_Input;

};