#pragma once
#include "pch.h"
#include "Input/Input.hpp"

// klasa aplikacji
class App {
public:
	App();
	~App();

	void run();
private:
	sf::RenderWindow m_window;

private:
	// okno wej�cia
	Input m_input;
};

