#include "pch.h"
#include "Atari.hpp"

Atari::Atari() {
	tLang::tCode t_atariSettings("atariSettings");
	
	std::future<bool> texture_thread;
	// wczytanie z pliku tekstury ��wia
	if (t_atariSettings["turtle"]["texture"]) {
		m_turtleTexture = new sf::Texture();

		// �adowanie tekstury na drugim watku
		texture_thread = std::async(std::launch::async, util::getTexture, t_atariSettings["turtle"]["texture"]->value, m_turtleTexture);
	}
	else
		throw std::runtime_error("Couldn't find \"texture\" in atariSettings");

	// odebranie tekstury od drugiego rdzenia
	if (!texture_thread.get())
		throw std::runtime_error("Couldn't load turtle texture!");

	// stworzenie pierwszego (domy�lnego) ��wia
	m_turtles.push_back(Turtle());
}

Atari::~Atari() {
	delete m_turtleTexture;
	m_turtleTexture = nullptr;
	m_turtles.clear();
}

Atari& Atari::Get() {
	static Atari atari;
	return atari;
}

void Atari::DrawCanvas(sf::RenderWindow& window) {
	Canvas::Get().DrawOnScreen(window);
	// narysowanie ��wi
	{
		for (int i = 0; i < m_turtles.size(); i++)
			m_turtles[i].Draw(window);
	}
}

void Atari::DrawUI() {
	{ // tabela z ��wiami
		ImGui::Columns(2);
		ImGui::SetColumnOffset(1, 200.f);

		// tabela z ��wiami
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
		// wypisanie danych na temat wybranego ��wia
		{
			// stworzenie tymczasowej struktury
			TurtleData temp_data = m_turtles[activeTab].getTurtleData();

			// odwr�cenie osi Y (tak, aby by�o bardziej intuicyjnie)
			temp_data.currentPosition.y *= -1;

			{ // wypisanie pozycji
				ImGui::Text("Aktualna pozycja: %d, %d",
					temp_data.currentPosition.x, temp_data.currentPosition.y);
			}

			{ // wypisanie rotacji
				ImGui::Text("Obrot: %d stopni", (int)temp_data.rotation);
			}

			// checkboxy z danymi na temat sladu i widocznosci
			ImGui::Checkbox("Widoczny", &temp_data.visible);

			// checkbox w tej samej linii
			ImGui::SameLine();

			ImGui::Checkbox("Zostawia slad", &temp_data.penDown);

			// checkbox w tej samej linii
			ImGui::SameLine();

			ImGui::Checkbox("Aktywny", &temp_data.active);
		}

		
		
	}

}

void Atari::Update() {

}
