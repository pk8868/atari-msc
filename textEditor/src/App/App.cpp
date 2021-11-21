#include "pch.h"
#include "App.hpp"

App::App() {
	// za�adowanie pliku konfiguracyjnego
	tLang::tCode t_configFile("config");

	// stworzenie okna
	{
		// sprawdzenie i za�adowanie rozmiaru okna
		sf::Vector2i temp_windowSize(800, 600);
		if (t_configFile["userPreference"]["windowSize"])
			temp_windowSize = sf::Vector2i(t_configFile["userPreference"]["windowSize"]->v2f());


		// sprawdzenie i za�adowanie tytu�u 
		std::string temp_windowName = "Atari";
		if (t_configFile["appData"]["appTitle"])
			temp_windowName = t_configFile["appData"]["appTitle"]->value;
		
		
		m_window.create(sf::VideoMode(temp_windowSize.x, temp_windowSize.y),
						temp_windowName,
						sf::Style::Default);
	}

	// ustawienie maksymalnego frameratu
	m_window.setFramerateLimit(60);


	// je�li jest zdefiniowana sciezka do nowej czcionki, za�aduj j�
	if (t_configFile["appData"]["fontLoc"]) {
		// wy��czenie �adowania domy�lnej czcionki
		ImGui::SFML::Init(m_window, false);

		float fontSize = 20.f;
		// ustalenie rozmiaru czcionki w pikselach
		if (t_configFile["userPreference"]["fontSize"])
			fontSize = t_configFile["userPreference"]["fontSize"]->fp32();

		// za�adowanie z pliku
		ImGui::GetIO().Fonts->AddFontFromFileTTF(
								t_configFile["appData"]["fontLoc"]->value.c_str(),
								fontSize);

		// zupdateowanie czcionek imgui
		ImGui::SFML::UpdateFontTexture();
	}
	// w przeciwnym wypadku za�aduj domy�ln� czcionk�
	else
		ImGui::SFML::Init(m_window);



}

App::~App() {
	ImGui::SFML::Shutdown();
}
