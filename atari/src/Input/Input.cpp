#include "pch.h"
#include "Input.hpp"

#define INPUTSIZE 100

Input::Input(sf::RenderWindow* r_window)
	:r_window(r_window)
{
	clear();
}

Input::~Input() {

}

void Input::Update(const std::string& errorCodes) {

	{
		sf::Vector2f temp_windowsize((float)r_window->getSize().x, r_window->getSize().y * 0.20f);
		// ustawienie pozycji i rozmiaru okna
		ImGui::SetNextWindowSize(ImVec2{ temp_windowsize });
		ImGui::SetNextWindowPos(ImVec2{ (sf::Vector2f)r_window->getSize() - temp_windowsize });
	}

	sf::Vector2f maxItemSize(r_window->getSize().x - ImGui::GetStyle().WindowPadding.x,
				(r_window->getSize().y * 0.20f) - ImGui::GetStyle().WindowPadding.y);

	ImGui::Begin("Atari Interpreter", NULL, 
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize	|
		ImGuiWindowFlags_NoMove		|
		ImGuiWindowFlags_NoCollapse);

	if (ImGui::BeginTabBar("Opcje"))
	{

		if (ImGui::BeginTabItem("Wejscie"))
		{ // okienko z inputem

			ImGui::EndTabItem();
			// miejsce na tekst
			ImGui::PushItemWidth(maxItemSize.x - 150.f);
			if (ImGui::InputText("", (char*)p_Input.inputText.c_str(), INPUTSIZE, ImGuiInputTextFlags_EnterReturnsTrue))
				p_Input.shouldReturn = true;
			ImGui::PopItemWidth();


			// przycisk w tej samej lini
			ImGui::SameLine();
			// przycisk do wykonania poleceñ
			if (ImGui::Button("Wykonaj", ImVec2(150.f, 0.f)))
				p_Input.shouldReturn = true;
		}

		if (ImGui::BeginTabItem("Konsola Interpretera"))
		{ // okienko z bledami
			ImGui::EndTabItem();
			
			ImGui::Text(errorCodes.c_str());
		}

		if (ImGui::BeginTabItem("Atari"))
		{
			ImGui::EndTabItem();
			// stan zolwi
			Atari::Get().DrawUI();
		}

		ImGui::EndTabBar();
	}
	

	ImGui::End();
}

std::string Input::getString() {
	p_Input.shouldReturn = false;

	return p_Input.inputText;
}

void Input::clear() {
	p_Input.inputText = "";
	p_Input.inputText.resize(INPUTSIZE);
}
