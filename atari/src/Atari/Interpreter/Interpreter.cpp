#include "pch.h"
#include "Interpreter.hpp"

Interpreter::Interpreter(std::vector<Turtle>& turtles)
	:r_turtles(turtles)
{

}

ErrorList Interpreter::interpretCode(std::string code) {
	{
		perf::ScopeClock interpreter("Interpreter");

		m_instructionSets.clear();

		// zmniejszenie do faktycznego rozmiaru
		m_list.clear();

		SetPList setList{};

		// parsowanie kodu (duze wyrazy)
		pParse(code, setList, m_list);

		for (int i = 0; i < setList.size(); i++)
			pInterpret(setList[i], m_list);

	}

	if (!m_list.size()) {
		// ¿ó³w wykonuje polecenia jesli nie ma bledow
		for (int i = 0; i < m_instructionSets.size(); i++)
			r_turtles[0].ExecuteInstructionSet(m_instructionSets[i]);
	}


	pCreateErrorString();

	return m_list;
}

void Interpreter::Draw() {
	ImGui::Begin("Konsola interpretera");
	ImGui::Text(m_errorString.c_str());
	ImGui::End();
}

bool Interpreter::ifEmptyString(const std::string& string) {
	for (int i = 1; i < string.size(); i++) {
		if (string[i] != string[i - 1])
			return false;
	}
	return true;
}

void Interpreter::pCreateErrorString() {
	m_errorString.clear();
	std::stringstream stream;
	for (int i = 0; i < m_list.size(); i++)
		stream << (int)m_list[i].code << " - " << m_list[i].message << "\n";

	m_errorString = stream.str();
}

// po koñcu repeata zostaje spacja po ] i wszystkie komendy po nim s¹ Ÿle interpretowane
void Interpreter::pDeleteSpaces(std::string& string) {
	while (string[0] == ' ')
		string.erase(0, 1);
}