#pragma once
#include "pch.h"
#include "Input/Input.hpp"
#include "Atari/Atari.hpp"

// klasa aplikacji
class App {
public:
	App();
	~App();

	void run();
private:
	// okno aplikacji
	sf::RenderWindow m_window;


	// plik konfiguracyjny
	tLang::tCode m_configFile;

private:
	// okno wej�cia
	Input m_input;

	// instancja atari
	//Atari m_atari;
};

