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
	// okno wejœcia
	Input m_input;

	// instancja atari
	std::unique_ptr<Atari> m_atari = nullptr;

	// watek do zapisywania screenshotow
	std::future<void> secondThread;
private:
	// g³ówne menu aplikacji
	void p_mainMenu();
	

private:
	const std::vector<std::string> smThemes{ "light", "dark", "classic" };

	struct AppSettings {
		sf::Vector2i windowSize;
		int fontSize;
		std::string theme;
	} m_appSettings{ sf::Vector2i(1280, 720), 18, smThemes[0] };

	void pSaveSettings();

	// okno ustawieñ
	bool m_SettingsOpened = false;
	void pSettings();
};

