#include "pch.h"
#include "App.hpp"

App::App() {
	// za³adowanie pliku konfiguracyjnego
	m_configFile.addFile("config");

	// stworzenie okna
	{
		// sprawdzenie i za³adowanie rozmiaru okna
		sf::Vector2i temp_windowSize(800, 600);
		if (m_configFile["userPreference"]["windowSize"])
			temp_windowSize = sf::Vector2i(m_configFile["userPreference"]["windowSize"]->v2f());


		// sprawdzenie i za³adowanie tytu³u 
		std::string temp_windowName = "Atari";
		if (m_configFile["appData"]["appTitle"])
			temp_windowName = m_configFile["appData"]["appTitle"]->value;
		
		
		m_window.create(sf::VideoMode(temp_windowSize.x, temp_windowSize.y),
						temp_windowName,
						sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(0, 0, 8));

		// ustawienie ikonki programu
		if (m_configFile["appData"]["iconLoc"]) {
			sf::Image temp_img;
			temp_img.loadFromFile(m_configFile["appData"]["iconLoc"]->value);

			m_window.setIcon(16, 16, temp_img.getPixelsPtr());
		}
	}

	// ustawienie maksymalnego frameratu
	m_window.setFramerateLimit(60);


	// jeœli jest zdefiniowana sciezka do nowej czcionki, za³aduj j¹
	if (m_configFile["appData"]["fontLoc"]) {
		// wy³¹czenie ³adowania domyœlnej czcionki
		ImGui::SFML::Init(m_window, false);

		float fontSize = 20.f;
		// ustalenie rozmiaru czcionki w pikselach
		if (m_configFile["userPreference"]["fontSize"])
			fontSize = m_configFile["userPreference"]["fontSize"]->fp32();

		// za³adowanie z pliku
		ImGui::GetIO().Fonts->AddFontFromFileTTF(
								m_configFile["appData"]["fontLoc"]->value.c_str(),
								fontSize);

		// zupdateowanie czcionek imgui
		ImGui::SFML::UpdateFontTexture();
	}
	// w przeciwnym wypadku za³aduj domyœln¹ czcionkê
	else
		ImGui::SFML::Init(m_window);

	// stworzenie instancji atari
	m_atari = std::make_unique<Atari>(AppData{ sf::Vector2i(m_window.getSize()) });
}

App::~App() {
	ImGui::SFML::Shutdown();

	// zapisanie wszystkiego do pliku konfiguracyjnego
	tLang::saveToFile(m_configFile, "config");
}
