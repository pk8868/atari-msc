#include "pch.h"
#include "Interpreter.hpp"


#define SET_INSTRUCTION(x) if (current.find(#x) != std::string::npos) \
						currentInstruction.instruction = TurtleInstructions::x

void Interpreter::pInterpret(SetPrecursor& precursor, ErrorList& errorList) {
	InstructionSet temp_Set;


	struct InterpretingStatus {
		bool expectingArg = false;
	} status;

	Instruction currentInstruction{ TurtleInstructions::None, 0};

	std::stringstream stream(precursor.code);
	std::string current;

	while (std::getline(stream, current, ' ')) {
		if (status.expectingArg) {
			// !!! SPRAWDZI� CZY TO LICZBA
			currentInstruction.arg = atoi(current.c_str());

			temp_Set.instructions.push_back(currentInstruction);
			currentInstruction = Instruction{ TurtleInstructions::None, 0 };

			// wrocenie do wyszukiwania polecenia
			status.expectingArg = false;
		}
		else {
			// paskudny if
			// DO PRZODU
			SET_INSTRUCTION(FD);
			// DO TY�U
			else SET_INSTRUCTION(BK);
			// W PRAWO
			else SET_INSTRUCTION(RT);
			// W LEWO
			else SET_INSTRUCTION(LT);

			// OPU�� PISAK
			else SET_INSTRUCTION(PU);
			// PODNIE� PISAK
			else SET_INSTRUCTION(PD);
			// POKA� �ӣWIA
			else SET_INSTRUCTION(ST);
			// UKRYJ �ӣWIA
			else SET_INSTRUCTION(HT);
			// WYCZYSC EKRAN
			else SET_INSTRUCTION(CS);
			// ERROR
			else
				errorList.emplace_back(ErrorCode::UnknownCommand, " nieznana komenda " + current);

			// poprawka, pozwala wychwytywa� bl�dne polecenia gdy wyst�puj� jedna po drugiej
			if (currentInstruction.instruction != TurtleInstructions::None)
				status.expectingArg = (int)currentInstruction.instruction & 0x1;

			// jesli nie spodziewa sie argumentu dodaje go do listy instrukcji
			if (!status.expectingArg) {
				temp_Set.instructions.push_back(currentInstruction);
				currentInstruction = Instruction{ TurtleInstructions::None, 0 };
			}
		}
	}

	temp_Set.set_data.repeat = precursor.repeat;
	m_instructionSets.push_back(temp_Set);
}