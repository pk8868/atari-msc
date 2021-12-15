#include "pch.h"
#include "App.hpp"
#include "Utils/Utils.hpp"

void App::run() {
	sf::Event l_event;
	sf::Clock l_clock;
	sf::Time s_frameTime;
	float frameTime = 0.f;


	std::future<void> secondThread;
	while (true) {
		// handlowanie event�w
		while (m_window.pollEvent(l_event)) {
			// obs�uga eventu klikni�cia x
			if (l_event.type == sf::Event::Closed) {
				m_window.close();
				break;
			}
			else {
				if (l_event.type == sf::Event::KeyReleased &&
					l_event.key.code == sf::Keyboard::Key::F11) {
					// zapisywanie do pliku na drugim w�tku
					secondThread = std::async(std::launch::async, util::saveToFile, m_atari->getCanvas().getImage(),
						"elo.png");
				}

				ImGui::SFML::ProcessEvent(m_window, l_event);
			}
		}

		// wyj�cie z p�tli
		if (!m_window.isOpen())
			break;

		// updateowanie czasu klatki
		s_frameTime = l_clock.restart();
		frameTime = s_frameTime.asSeconds();

		// updatowanie element�w gui
		ImGui::SFML::Update(m_window, s_frameTime);


		m_atari->Update();

		// wyczyszczenie ekranu
		m_window.clear();

		// zupdatowanie okna z inputem
		m_input.Update();

		// aktualizacja instancji Atari
		m_atari->Draw(m_window);

		// wyrenderowanie imgui na ekran
		ImGui::SFML::Render(m_window);

		// wyrenderowanie
		m_window.display();


		// odebranie danych wej�ciowych
		if (m_input.shouldGet()) {
			m_input.getString(); // wys�a� do interpretera atari
			m_input.clear();
		}

	}
}