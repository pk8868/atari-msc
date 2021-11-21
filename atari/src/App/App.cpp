#include "pch.h"
#include "App.hpp"

App::App() {
	// za³adowanie pliku konfiguracyjnego
	tLang::tCode t_configFile("config");

	// stworzenie okna
	{
		// sprawdzenie i za³adowanie rozmiaru okna
		sf::Vector2i temp_windowSize(800, 600);
		if (t_configFile["userPreference"]["windowSize"])
			temp_windowSize = sf::Vector2i(t_configFile["userPreference"]["windowSize"]->v2f());


		// sprawdzenie i za³adowanie tytu³u 
		std::string temp_windowName = "Atari";
		if (t_configFile["appData"]["appTitle"])
			temp_windowName = t_configFile["appData"]["appTitle"]->value;
		
		
		m_window.create(sf::VideoMode(temp_windowSize.x, temp_windowSize.y),
						temp_windowName,
						sf::Style::Default);
	}

	// ustawienie maksymalnego frameratu
	m_window.setFramerateLimit(60);


	// jeœli jest zdefiniowana sciezka do nowej czcionki, za³aduj j¹
	if (t_configFile["appData"]["fontLoc"]) {
		// wy³¹czenie ³adowania domyœlnej czcionki
		ImGui::SFML::Init(m_window, false);

		float fontSize = 20.f;
		// ustalenie rozmiaru czcionki w pikselach
		if (t_configFile["userPreference"]["fontSize"])
			fontSize = t_configFile["userPreference"]["fontSize"]->fp32();

		// za³adowanie z pliku
		ImGui::GetIO().Fonts->AddFontFromFileTTF(
								t_configFile["appData"]["fontLoc"]->value.c_str(),
								fontSize);

		// zupdateowanie czcionek imgui
		ImGui::SFML::UpdateFontTexture();
	}
	// w przeciwnym wypadku za³aduj domyœln¹ czcionkê
	else
		ImGui::SFML::Init(m_window);



}

App::~App() {
	ImGui::SFML::Shutdown();
}
