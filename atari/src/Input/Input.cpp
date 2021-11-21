#include "pch.h"
#include "Input.hpp"

Input::Input() {
	p_Input.inputText.resize(64);
}

Input::~Input() {

}

void Input::Update() {
	ImGui::Begin("Input");
	// miejsce na tekst
	ImGui::InputText("", (char*)p_Input.inputText.c_str(), 64);

	// przycisk do wykonania poleceñ
	if (ImGui::Button("Wykonaj"))
		p_Input.shouldReturn = true;
	ImGui::End();
}

std::string Input::getString() {
	p_Input.shouldReturn = false;

	return p_Input.inputText;
}

void Input::clear() {
	p_Input.inputText = "";
	p_Input.inputText.resize(64);
}
