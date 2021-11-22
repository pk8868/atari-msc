#include "pch.h"
#include "Atari.hpp"

Atari::Atari(const AppData& appData)
	:m_appData(appData)
{
	tLang::tCode t_atariSettings("atariSettings");
	
	// stworzenie planszy
	m_canvas = std::make_unique<Canvas>(appData.windowSize);
	// stworzenie instancji interpretera
	m_interpreter = std::make_unique<Interpreter>(m_turtles);




	// wczytanie z pliku tekstury ¿ó³wia
	if (t_atariSettings["turtle"]["texture"]) {
		m_turtleTexture = new sf::Texture();
		if (!m_turtleTexture->loadFromFile(t_atariSettings["turtle"]["texture"]->value))
			throw std::runtime_error("Couldn't load turtle texture");
		m_turtleTexture->setSmooth(true);
	}
	else
		throw std::runtime_error("Couldn't find texture in atariSettings");

	// stworzenie pierwszego (domyœlnego) ¿ó³wia
	m_turtles.emplace_back(appData.windowSize, m_turtleTexture);
}

Atari::~Atari() {
	delete m_turtleTexture;
}

void Atari::Draw(sf::RenderWindow& window) {
	m_canvas->Clear();
	m_canvas->Draw(sf::Vector2f(m_appData.windowSize / 2),
		sf::Vector2f(sf::Mouse::getPosition(window)), sf::Color::Red);

	m_canvas->DrawOnScreen(window);

	{
		int activeTab = 0;
		ImGui::Begin("ATARI");

		// tabela z ¿ó³wiami
		if (ImGui::BeginTabBar("tabela2")) {

			for (int i = 0; i < m_turtles.size(); i++) {
				std::string nazwa = "Zolw" + std::to_string(i);
				if (ImGui::BeginTabItem(nazwa.c_str())) {
					activeTab = i;
					ImGui::EndTabItem();
				}
			}

			ImGui::EndTabBar();
		}

		// wypisanie danych na temat wybranego ¿ó³wia
		{
			TurtleData temp_data = m_turtles[activeTab].getTurtleData();

			{ // wypisanie pozycji
				std::string temp_text = "Aktualna pozycja: "
					+ std::to_string(int(temp_data.currentPosition.x)) + ", "
					+ std::to_string(int(temp_data.currentPosition.y));


				ImGui::Text(temp_text.c_str());
			}
			{
				std::string temp_text = "Obrot: "
					+ std::to_string(int(temp_data.rotation)) + " stopni";


				ImGui::Text(temp_text.c_str());
			}

			// checkboxy z danymi na temat sladu i widocznosci
			ImGui::Checkbox("Widoczny", &temp_data.visible);
			ImGui::Checkbox("Zostawia slad", &temp_data.penDown);
		}

		ImGui::End();
	}

	// narysowanie ¿ó³wi
	{
		for (int i = 0; i < m_turtles.size(); i++)
			m_turtles[i].Draw(window);
	}
	

}

void Atari::Update() {

}
