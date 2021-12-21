#pragma once
#include "pch.h"
#include "Input/Input.hpp"
#include "Atari/Atari.hpp"

// klasa aplikacji
class App {
private:
	const std::vector<std::string> smThemes{ "light", "dark", "classic" };
public:
	struct AppSettings {
		sf::Vector2i windowSize;
		int fontSize;
		std::string theme;
	} m_appSettings{ sf::Vector2i(1280, 720), 18, smThemes[0] };

public:
	App();
	~App();


	static App& Get();

	void run();
private:
	// okno aplikacji
	sf::RenderWindow m_window;


	// plik konfiguracyjny
	tLang::tCode m_configFile;

	// plik konfiguracyjny ImGui
	tLang::tCode m_imguiConfigFile;

private:
	// okno wejœcia
	Input m_input;

	// watek do zapisywania screenshotow
	std::future<void> secondThread;
private:
	// g³ówne menu aplikacji
	void p_mainMenu();

	void pSaveSettings();

	// okno ustawieñ
	bool m_SettingsOpened = false;
	void pSettings();
};

