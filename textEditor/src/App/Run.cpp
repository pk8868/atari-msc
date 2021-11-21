#include "pch.h"
#include "App.hpp"

void App::run() {
	sf::Event l_event;
	sf::Clock l_clock;
	sf::Time s_frameTime;
	float frameTime = 0.f;


	while (true) {
		// handlowanie event�w
		while (m_window.pollEvent(l_event)) {
			if (l_event.type == sf::Event::Closed) {
				m_window.close();
				break;
			}
			else if (l_event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, l_event.size.width, l_event.size.height);
				m_window.setView(sf::View(visibleArea));
			}
			else {
				ImGui::SFML::ProcessEvent(m_window, l_event);
			}
		}
		if (!m_window.isOpen())
			break;

		// updateowanie czasu klatki
		s_frameTime = l_clock.restart();
		frameTime = s_frameTime.asSeconds();

		// updatowanie element�w
		ImGui::SFML::Update(m_window, s_frameTime);


		// wyczyszczenie ekranu
		m_window.clear();

		m_input.Update();


		ImGui::SFML::Render(m_window);

		// wyrenderowanie
		m_window.display();


		// odebranie danych wej�ciowych
		if (m_input.shouldGet())
			m_input.getString(); // wys�a� do interpretera atari

	}
}