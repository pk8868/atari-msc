#include "pch.h"
#include "App.hpp"
#include "Utils/Utils.hpp"

// macro do zapisywania planszy
void App::run() {
	sf::Event l_event;
	sf::Clock l_clock;
	sf::Time l_frameTime;

	// glowna petla
	while (true) {
		// handlowanie eventów
		while (m_window.pollEvent(l_event)) {
			// obs³uga eventu klikniêcia x
			if (l_event.type == sf::Event::Closed) {
				m_window.close();
				break;
			}
			else {
				if (l_event.type == sf::Event::KeyReleased) {
					// F5 - logger
					if (l_event.key.code == sf::Keyboard::Key::F5)
						// zmiana stanu okna
						ErrorLog::Toggle();
				}
				else if (l_event.type == sf::Event::Resized) {
					// zmiana rozmiaru okna na nowy
					m_window.setSize(sf::Vector2u(l_event.size.width, l_event.size.height));

					// zmiana widoku
					m_window.setView(sf::View(sf::FloatRect(0.f, 0.f,
						(float)l_event.size.width, (float)l_event.size.height)));

					// aktualizacja ustawieñ i canvasu
					m_appSettings.windowSize = sf::Vector2i(m_window.getSize());
					Canvas::Get().newWindowSize(m_window.getSize());
				}


				ImGui::SFML::ProcessEvent(m_window, l_event);
			}
		}

		// wyjœcie z pêtli
		if (!m_window.isOpen())
			break;

		// updateowanie czasu klatki
		l_frameTime = l_clock.restart();

		// updatowanie elementów gui
		ImGui::SFML::Update(m_window, l_frameTime);


		//Atari::Get().Update();

		// wyczyszczenie ekranu
		m_window.clear(sf::Color::White);

		// narysowanie canvasu na oknie
		Atari::Get().DrawCanvas(m_window);

		// narysowanie loggera
		ErrorLog::Draw();

		// zupdatowanie okna z interfejsem u¿ytkownika
		m_input.Update(Interpreter::Get().getErrorString());

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
			Interpreter::Get().interpretCode(m_input.getString());
			m_input.clear();
		}

	}
}

void App::p_mainMenu() {
	ImGui::BeginMainMenuBar();

	// menu File
	if (ImGui::BeginMenu("Plik")) {
		if (ImGui::MenuItem("Zapisz")) {
			std::string filename = util::saveFileDialog("PNG Files (*.png)\0*.png\0\0");
			if (filename != "") {
				if (!util::saveToFile(Canvas::Get().getImage(), filename))
					ErrorLog::Log(Error{ Error::Warning, "Couldn't save " + filename });
			}
		}

		if (ImGui::MenuItem("Wyjdz"))
			m_window.close();

		ImGui::EndMenu();
	}

	if (ImGui::MenuItem("Ustawienia"))
		m_SettingsOpened = !m_SettingsOpened;

	if (ImGui::MenuItem("Pomoc"))
		// wywo³anie przegl¹darki dla dokumentu html, dwa \ bo nie zadzia³a z normalnym /
		ShellExecuteA(NULL, "open", "doc\\index.html", NULL, NULL, SW_SHOWNORMAL);


	ImGui::EndMainMenuBar();
}

void App::pSettings() {
	// nowe okno ImGUI
	
	ImGui::Begin("Ustawienia", &m_SettingsOpened,
		ImGuiWindowFlags_NoCollapse);

	// rozmiar czcionki
	ImGui::SliderInt("Rozmiar czcionki (px)", &m_appSettings.fontSize, 12, 40);
	{ // wybieranie rozdzielczoœci

		// kombo
		if (ImGui::BeginCombo("Motyw",
			m_appSettings.theme.c_str())) {
			
			for (const auto& theme : smThemes) {
				if (ImGui::Selectable(theme.c_str())) {
					// jeœli jest wybrany zmiana nazwy motywu
					m_appSettings.theme = theme;

					// zresetowanie opcji stylu
					util::resetStyle();

					// ustawienie motywu
					util::setTheme(m_appSettings.theme);

					// wczytanie g³ównych ustawieñ
					util::changeStyle(m_imguiConfigFile[0]);

					// wczytanie ustawieñ wybranego stylu
					util::changeStyle(m_imguiConfigFile[m_appSettings.theme]);
				}
			}

			ImGui::EndCombo();
		}

	}

	// warning
	ImGui::Text("UWAGA: Zmiana niektorych ustawien wymaga restartu aplikacji!");
	ImGui::End();
}
