#include "pch.h"
#include "Interpreter.hpp"
#include "Atari/Atari.hpp"

Interpreter::Interpreter() {
	;
}

Interpreter& Interpreter::Get()
{
	static Interpreter interpreter;
	return interpreter;
}

ErrorList Interpreter::interpretCode(std::string code) {
#ifdef PERFMON
	perf::ScopeClock i_clock("Interpreter");
#endif
	{

		m_instructionSets.clear();

		// zmniejszenie do faktycznego rozmiaru
		m_list.clear();

		SetPList setList{};

		// parsowanie kodu (duze wyrazy)
		pParse(code, setList);

		for (int i = 0; i < setList.size(); i++)
			pInterpret(setList[i]);

		
	}

	// jeœli nie ma errorów
	if (!m_list.size()) {
		// ¿ó³w wykonuje polecenia jesli nie ma bledow
		for (int i = 0; i < m_instructionSets.size(); i++) {
			for (int j = 0; j < m_instructionSets[i].set_data.repeat; j++) {
				for (int n = 0; n < m_instructionSets[i].instructions.size(); n++) {
					switch (m_instructionSets[i][n].instruction) {
					case Instructions::CS:
						Canvas::Get().Clear();
						break;
					case Instructions::TELL:
						// podmiana aktywnych ¿ó³wi
						m_activeTurtles = m_instructionSets[i][n].arg;
						for (int i = 0; i < m_activeTurtles.size(); i++) {
							// za duze id
							if (m_activeTurtles[i] > Atari::Get().getTurtles().size()) {
								m_list.emplace_back(ErrorCode::InvalidTurtleID, " zle ID zolwia!");
							}
							// dodanie zolwia
							else if (m_activeTurtles[i] == Atari::Get().getTurtles().size())
								Atari::Get().getTurtles().push_back(Turtle());
						}
						markInactiveTurtles();
						break;
					default:
						// wykonanie operacji dla kazdego aktywnego zolwia
						for (int x = 0; x < Atari::Get().getTurtles().size(); x++)
							Atari::Get().getTurtles()[x].ExecuteInstructionSet(m_instructionSets[i][n]);
						break;
					}
				}
			}
		}
	}

	pCreateErrorString();
	return m_list;
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

void Interpreter::markInactiveTurtles() {
	for (int i = 0; i < Atari::Get().getTurtles().size(); i++) {
		bool active = false;
		for (int j = 0; j < m_activeTurtles.size(); j++) {
			// jesli znajdzie na liscie zolwia
			if (m_activeTurtles[j] == i) {
				active = true;
				break;
			}
		}
		Atari::Get().getTurtles()[i].getTurtleDataRef().active = active;
	}
}
