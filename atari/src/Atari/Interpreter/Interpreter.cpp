#include "pch.h"
#include "Interpreter.hpp"

Interpreter::Interpreter(std::vector<Turtle>& turtles)
	:r_turtles(turtles)
{

}

ErrorList Interpreter::interpretCode(std::string code) {
	m_instructionSets.clear();

	// zmniejszenie do faktycznego rozmiaru
	ErrorList list{};

	SetPList setList{};

	// parsowanie kodu (duze wyrazy)
	pParse(code, setList, list);

	for (int i = 0; i < setList.size(); i++)
		pInterpret(setList[i], list);

	// ¿ó³w wykonuje polecenia
	for (int i = 0; i < m_instructionSets.size(); i++)
		r_turtles[0].ExecuteInstructionSet(m_instructionSets[i]);


	for (int i = 0; i < list.size(); i++)
		std::cout << (short)list[i].code << "-" << list[i].message << "\n";

	return list;
}

void Interpreter::Draw() {

}

bool Interpreter::ifEmptyString(const std::string& string) {
	for (int i = 1; i < string.size(); i++) {
		if (string[i] != string[i - 1])
			return false;
	}
	return true;
}