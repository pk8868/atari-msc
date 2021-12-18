#include "pch.h"
#include "App.hpp"

// za³adowanie stylu
static void LoadStyle(bool* readyStyle) {
	// za³adowanie pliku
	tLang::tCode imguiFile("imgui");

	// zaczekaj na imgui init
	while (!(*readyStyle)) { Sleep(10); }
	
	
	// stworzenie stylu
	util::changeStyle(imguiFile[0]);
}

static void app_LoadIcon(std::string filename, sf::Image* img) {
	img->loadFromFile(filename);
}

App::App() {
	bool readyStyle = false;
	NEW_THREAD(styleLoader, void, LoadStyle, &readyStyle);

	// za³adowanie pliku konfiguracyjnego
	m_configFile.addFile("config");

	// rdzeñ do ³adowania ikony i jego zmienne
	std::future<void> iconLoader;
	bool loadIcon = false;
	sf::Image temp_img;

	// stworzenie okna
	{
		// sprawdzenie i za³adowanie rozmiaru okna
		{
			auto v_windowSize = m_configFile["userPreference"]["windowSize"];
			if (v_windowSize)
				m_appSettings.windowSize = sf::Vector2i(v_windowSize->v2f());
		}

		// sprawdzenie i za³adowanie tytu³u 
		{
			std::string temp_windowName = "Atari";
			auto v_windowName = m_configFile["appData"]["appTitle"];
			if (v_windowName)
				temp_windowName = v_windowName->value;

			{
				// stworzenie okna
				m_window.create(sf::VideoMode(m_appSettings.windowSize.x, m_appSettings.windowSize.y), temp_windowName,
					sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close, sf::ContextSettings(0, 0, 8));
			}
		}

		


		
		// ustawienie ikonki programu
		{
			auto v_iconLoc = m_configFile["appData"]["iconLoc"];
			if (v_iconLoc) {
				LAUNCH_THREAD(iconLoader, app_LoadIcon, v_iconLoc->value, &temp_img);
				loadIcon = true;
			}
		}
	}

	// wy³¹czenie ³adowania domyœlnej czcionki - przed stworzeniem atari, bo zasoby opengl sa w uzyciu
	auto v_fontLoc = m_configFile["appData"]["fontLoc"];
	if (v_fontLoc)
		ImGui::SFML::Init(m_window, false);

	// ustawienie maksymalnego frameratu
	m_window.setFramerateLimit(60);

	// stworzenie okna input
	m_input = Input(&m_window);

	// jeœli jest zdefiniowana sciezka do nowej czcionki, za³aduj j¹
	if (v_fontLoc) {
		// ustalenie rozmiaru czcionki w pikselach
		{
			auto v_fontSize = m_configFile["userPreference"]["fontSize"];
			if (v_fontSize)
				m_appSettings.fontSize = v_fontSize->i32();
		}

		// za³adowanie z pliku
		ImGui::GetIO().Fonts->AddFontFromFileTTF(
								v_fontLoc->value.c_str(),
								(float)m_appSettings.fontSize);

		// zupdateowanie czcionek imgui
		ImGui::SFML::UpdateFontTexture();
	}
	// w przeciwnym wypadku za³aduj domyœln¹ czcionkê
	else
		ImGui::SFML::Init(m_window);

	// ustawienie motywu aplikacji
	auto v_theme = m_configFile["userPreference"]["theme"];
	if (v_theme)
		m_appSettings.theme = v_theme->value;

	
	if (!util::setTheme(m_appSettings.theme))
		m_appSettings.theme = "dark"; // jesli jest niepoprawna nazwa motywu ustaw na dark

	readyStyle = true;

	// stworzenie instancji atari
	m_atari = std::make_unique<Atari>(AppData{ sf::Vector2i(m_window.getSize()) });


	// jesli jest ladowana ikona zaczekaj az skoncza sie ladowac
	if (loadIcon)
		JOIN_THREAD(iconLoader);

	m_window.setIcon(temp_img.getSize().x, temp_img.getSize().y, temp_img.getPixelsPtr());

	// zaczekaj az style skoñcz¹ siê ³adowaæ
	JOIN_THREAD(styleLoader);
}

App::~App() {
	// wylaczenie imgui
	ImGui::SFML::Shutdown();

	// zapisanie ustawieñ do pliku
	pSaveSettings();

	// zapisanie wszystkiego do pliku konfiguracyjnego
	tLang::saveToFile(m_configFile, "config");
}

void App::pSaveSettings() {
	// stworzenie struktury userPreference
	if (m_configFile["userPreference"].id != "userPreference")
		m_configFile.addDataStructure(tLang::DataStructure("userPreference", 3));

	auto& t_userPreference = m_configFile["userPreference"];

	// zapisanie rozmiaru okna 
	if (t_userPreference["windowSize"])
		t_userPreference["windowSize"]->value = util::vec2ToString(m_appSettings.windowSize);
	else
		t_userPreference.addVariable("windowSize", util::vec2ToString(m_appSettings.windowSize));

	// zapisanie rozmiaru czcionki
	if (t_userPreference["fontSize"])
		t_userPreference["fontSize"]->value = std::to_string(m_appSettings.fontSize);
	else
		t_userPreference.addVariable("fontSize", std::to_string(m_appSettings.fontSize));

	// zapisanie motywu
	if (t_userPreference["theme"])
		t_userPreference["theme"]->value = m_appSettings.theme;
	else
		t_userPreference.addVariable("theme", m_appSettings.theme);
}