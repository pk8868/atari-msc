#include "pch.h"
#include "App.hpp"

// za�adowanie stylu
static void LoadStyle(bool* readyStyle) {
	// za�adowanie pliku
	tLang::tCode imguiFile("imgui");

	// zaczekaj na imgui init
	while (!(*readyStyle)) { Sleep(10); }

	// stworzenie stylu
	util::changeStyle(imguiFile[0]);
}

App::App() {
	bool readyStyle = false;
	NEW_THREAD(styleLoader, void, LoadStyle, &readyStyle);

	// za�adowanie pliku konfiguracyjnego
	m_configFile.addFile("config");

	// stworzenie okna
	{
		// sprawdzenie i za�adowanie rozmiaru okna
		sf::Vector2i temp_windowSize(800, 600);
		if (m_configFile["userPreference"]["windowSize"])
			temp_windowSize = sf::Vector2i(m_configFile["userPreference"]["windowSize"]->v2f());


		// sprawdzenie i za�adowanie tytu�u 
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

	// wy��czenie �adowania domy�lnej czcionki - przed stworzeniem atari, bo zasoby opengl sa w uzyciu
	if (m_configFile["appData"]["fontLoc"])
		ImGui::SFML::Init(m_window, false);

	// ustawienie maksymalnego frameratu
	m_window.setFramerateLimit(60);

	// stworzenie okna input
	m_input = Input(&m_window);

	// je�li jest zdefiniowana sciezka do nowej czcionki, za�aduj j�
	if (m_configFile["appData"]["fontLoc"]) {

		float fontSize = 20.f;
		// ustalenie rozmiaru czcionki w pikselach
		if (m_configFile["userPreference"]["fontSize"])
			fontSize = m_configFile["userPreference"]["fontSize"]->fp32();

		// za�adowanie z pliku
		ImGui::GetIO().Fonts->AddFontFromFileTTF(
								m_configFile["appData"]["fontLoc"]->value.c_str(),
								fontSize);

		// zupdateowanie czcionek imgui
		ImGui::SFML::UpdateFontTexture();
	}
	// w przeciwnym wypadku za�aduj domy�ln� czcionk�
	else {
		ImGui::SFML::Init(m_window);
	}

	readyStyle = true;

	// stworzenie instancji atari
	m_atari = std::make_unique<Atari>(AppData{ sf::Vector2i(m_window.getSize()) });

	// zaczekaj az style sko�cz� si� �adowa�
	JOIN_THREAD(styleLoader);
}

App::~App() {


	// wylaczenie imgui
	ImGui::SFML::Shutdown();

	// zapisanie wszystkiego do pliku konfiguracyjnego
	tLang::saveToFile(m_configFile, "config");
}
