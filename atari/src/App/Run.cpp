#include "pch.h"
#include "App.hpp"
#include "Utils/Utils.hpp"

// macro do zapisywania planszy
#define SAVE_SCREENSHOT() secondThread = std::async(std::launch::async, util::saveToFile, m_atari->getCanvas().getImage(), "screenshots/" + util::getScreenshotTime() + ".png")
void App::run() {
	sf::Event l_event;
	sf::Clock l_clock;
	sf::Time s_frameTime;
	float frameTime = 0.f;

	while (true) {
		// handlowanie eventów
		while (m_window.pollEvent(l_event)) {
			// obs³uga eventu klikniêcia x
			if (l_event.type == sf::Event::Closed) {
				m_window.close();
				break;
			}
			else {
				if (l_event.type == sf::Event::KeyReleased &&
					l_event.key.code == sf::Keyboard::Key::F11) {
					// zapisywanie do pliku na drugim w¹tku
					SAVE_SCREENSHOT();
				}

				ImGui::SFML::ProcessEvent(m_window, l_event);
			}
		}

		// wyjœcie z pêtli
		if (!m_window.isOpen())
			break;

		// updateowanie czasu klatki
		s_frameTime = l_clock.restart();
		frameTime = s_frameTime.asSeconds();

		// updatowanie elementów gui
		ImGui::SFML::Update(m_window, s_frameTime);


		m_atari->Update();

		// wyczyszczenie ekranu
		m_window.clear(sf::Color::White);

		// narysowanie canvasu na oknie
		m_atari->DrawCanvas(m_window);

		// zupdatowanie okna z interfejsem u¿ytkownika
		m_input.Update(m_atari->getInterpreter().getErrorString(), *m_atari);

		// g³ówne menu programu
		p_mainMenu();

		// okno z ustawieniami
		if (m_SettingsOpened)
			pSettings();

		// wyrenderowanie imgui na ekran
		ImGui::SFML::Render(m_window);

		// wyrenderowanie
		m_window.display();


		// odebranie danych wejœciowych
		if (m_input.shouldGet()) {
			m_atari->getInterpreter().interpretCode(m_input.getString());
			m_input.clear();
		}

	}
}

void App::p_mainMenu() {
	ImGui::BeginMainMenuBar();

	if (ImGui::Button("Save"))
		SAVE_SCREENSHOT();

	if (ImGui::Button("Settings"))
		m_SettingsOpened = !m_SettingsOpened;

	if (ImGui::Button("Help"))
		// wywo³anie przegl¹darki dla dokumentu html, dwa \ bo nie zadzia³a z normalnym /
		ShellExecuteA(NULL, "open", "doc\\index.html", NULL, NULL, SW_SHOWNORMAL);


	ImGui::EndMainMenuBar();
}

void App::pSettings() {
	// nowe okno ImGUI
	
	ImGui::Begin("Settings", &m_SettingsOpened,
		ImGuiWindowFlags_NoCollapse);

	// rozmiar czcionki
	ImGui::SliderInt("Rozmiar czcionki (px)", &m_appSettings.fontSize, 14, 30);
	{ // wybieranie rozdzielczoœci	

		// kombo
		if (ImGui::BeginCombo("Rozdzielczosc",
			util::vec2ToString(m_appSettings.windowSize, "x").c_str())) {
			auto& temp_videoModes = sf::VideoMode::getFullscreenModes();

			for (int i = 0; i < temp_videoModes.size(); i++) {
				if (temp_videoModes[i].width >= 800 && temp_videoModes[i].height >= 600) {
					if (ImGui::Selectable(
						util::vec2ToString(sf::Vector2i(temp_videoModes[i].width, temp_videoModes[i].height), "x").c_str())) {
						// jeœli jest wybrany zmiana rozmiaru okna
						m_appSettings.windowSize = sf::Vector2i(temp_videoModes[i].width, temp_videoModes[i].height);
					}
				}
			}

			ImGui::EndCombo();
		}
		
		// kombo
		if (ImGui::BeginCombo("Motyw",
			m_appSettings.theme.c_str())) {
			
			for (int i = 0; i < smThemes.size(); i++) {
				if (ImGui::Selectable(smThemes[i].c_str()))
					// jeœli jest wybrany zmiana nazwy motywu
					m_appSettings.theme = smThemes[i];
			}

			ImGui::EndCombo();
		}

	}

	// warning
	ImGui::Text("UWAGA: Zmiana ustawien wymaga restartu aplikacji!");
	ImGui::End();
}
