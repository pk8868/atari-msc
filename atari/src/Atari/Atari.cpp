#include "pch.h"
#include "Atari.hpp"

Atari::Atari() {
	tLang::tCode t_atariSettings("atariSettings");
	
	std::future<bool> texture_thread;
	// wczytanie z pliku tekstury ¿ó³wia
	if (t_atariSettings["turtle"]["texture"]) {
		m_turtleTexture = new sf::Texture();

		// ³adowanie tekstury na drugim watku
		texture_thread = std::async(std::launch::async, util::getTexture, t_atariSettings["turtle"]["texture"]->value, m_turtleTexture);
	}
	else
		ErrorLog::Log(Error{ Error::Critical, "Couldn't find \"texture\" in atariSettings" });

	// odebranie tekstury od drugiego rdzenia
	if (!texture_thread.get())
		ErrorLog::Log(Error{ Error::Critical, "Couldn't load turtle texture!" });

	// stworzenie pierwszego (domyœlnego) ¿ó³wia
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

		auto defaultButtonColor = ImGui::GetStyle().Colors[ImGuiCol_Button];

		// tabela z ¿ó³wiami
		ImGui::BeginChild("menu");
		for (int i = 0; i < m_turtles.size(); i++) {
			bool changedColor = false;

			// zmiana koloru na aktywny
			if (activeTab == i) {
				ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
				changedColor = true;
			}

			// stworzenie przycisku
			if (ImGui::Button(("Zolw" + std::to_string(i)).c_str(), ImVec2{200.f - (2.f * (ImGui::GetStyle().ItemSpacing.x + ImGui::GetStyle().FramePadding.x)), 0.f}))
				activeTab = i;
			
			// przywrócenie zwyk³ego koloru
			if (changedColor)
				ImGui::PopStyleColor();
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
