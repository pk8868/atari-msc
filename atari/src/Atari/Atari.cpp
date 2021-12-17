#include "pch.h"
#include "Atari.hpp"

Atari::Atari(const AppData& appData)
	:m_appData(appData)
{
	tLang::tCode t_atariSettings("atariSettings");
	
	std::future<bool> texture_thread;
	// wczytanie z pliku tekstury ¿ó³wia
	if (t_atariSettings["turtle"]["texture"]) {
		m_turtleTexture = new sf::Texture();

		// ³adowanie tekstury na drugim watku
		texture_thread = std::async(std::launch::async, util::getTexture, t_atariSettings["turtle"]["texture"]->value, m_turtleTexture);
	}
	else
		throw std::runtime_error("Couldn't find \"texture\" in atariSettings");


	// stworzenie planszy
	m_canvas = std::make_unique<Canvas>(appData.windowSize);

	// wyczyszczenie planszy
	m_canvas->Clear();

	// stworzenie instancji interpretera
	m_interpreter = std::make_unique<Interpreter>(m_turtles);
	
	// odebranie tekstury od drugiego rdzenia
	if (!texture_thread.get())
		throw std::runtime_error("Couldn't load turtle texture!");


	// stworzenie pierwszego (domyœlnego) ¿ó³wia
	m_turtles.emplace_back(m_turtleTexture, m_canvas.get());
}

Atari::~Atari() {
	delete m_turtleTexture;
	m_turtleTexture = nullptr;
	m_turtles.clear();
}

void Atari::DrawCanvas(sf::RenderWindow& window) {
	m_canvas->DrawOnScreen(window);
	// narysowanie ¿ó³wi
	{
		for (int i = 0; i < m_turtles.size(); i++)
			m_turtles[i].Draw(window);
	}
}

void Atari::DrawUI() {
	{ // tabela z ¿ó³wiami
		ImGui::Columns(2);
		ImGui::SetColumnOffset(1, 200.f);

		// tabela z ¿ó³wiami
		ImGui::BeginChild("menu");
		for (int i = 0; i < m_turtles.size(); i++) {
			std::string nazwa = "Zolw" + std::to_string(i);

			// DO ZROBIENIA - POKAZYWANIE ZE PRZYCISK JEST AKTYWNY
			if (ImGui::Button(nazwa.c_str(), ImVec2{200.f - (2.f * (ImGui::GetStyle().ItemSpacing.x + ImGui::GetStyle().FramePadding.x)), 0.f})) {
				activeTab = i;
			}
		}
		ImGui::EndChild();

		ImGui::NextColumn();
		// wypisanie danych na temat wybranego ¿ó³wia
		{
			// stworzenie tymczasowej struktury
			TurtleData temp_data = m_turtles[activeTab].getTurtleData();

			// odwrócenie osi Y (tak, aby by³o bardziej intuicyjnie)
			temp_data.currentPosition.y *= -1;

			{ // wypisanie pozycji
				std::string temp_text = "Aktualna pozycja: "
					+ std::to_string(int(temp_data.currentPosition.x)) + ", "
					+ std::to_string(int(temp_data.currentPosition.y));


				ImGui::Text(temp_text.c_str());
			}

			{ // wypisanie rotacji
				std::string temp_text = "Obrot: "
					+ std::to_string(int(temp_data.rotation)) + " stopni";


				ImGui::Text(temp_text.c_str());
			}

			// checkboxy z danymi na temat sladu i widocznosci
			ImGui::Checkbox("Widoczny", &temp_data.visible);

			// checkbox w tej samej linii
			ImGui::SameLine();

			ImGui::Checkbox("Zostawia slad", &temp_data.penDown);
		}

		
		
	}

}

void Atari::Update() {

}
