#include "pch.h"
#include "Interpreter.hpp"


#define SET_INSTRUCTION(x) if (current.find(#x) != std::string::npos) \
						currentInstruction.instruction = Instructions::x

void Interpreter::pInterpret(SetPrecursor& precursor) {
	InstructionSet temp_Set;


	struct InterpretingStatus {
		short expectingArg = false;
	} status;

	Instruction currentInstruction{ Instructions::None, {0} };

	std::stringstream stream(precursor.code);
	std::string current;
	std::string argList = "";
	while (std::getline(stream, current, ' ')) {
		
		if (status.expectingArg) {
			// !!! SPRAWDZIÆ CZY TO LICZBA
			bool addVar = true;

			if (status.expectingArg == 1)
				getArgList(currentInstruction, current);
			else {
				argList += current + ",";

				addVar = current.find(']') != std::string::npos; 
				for (int i = 0; (i < current.length()) && current[i] != '\0'; i++) {
					std::cout << i << ": " << current[i] << "\n";
				}
				if (addVar) {
					getArgList(currentInstruction, argList);
					argList = "";
				}
			}

			if (addVar) {
				temp_Set.instructions.push_back(currentInstruction);
				currentInstruction = Instruction{ Instructions::None, {0} };

				// wrocenie do wyszukiwania polecenia
				status.expectingArg = false;
			}
		}
		else {
			// paskudny if
			// DO PRZODU
			SET_INSTRUCTION(FD);
			// DO TY£U
			else SET_INSTRUCTION(BK);
			// W PRAWO
			else SET_INSTRUCTION(RT);
			// W LEWO
			else SET_INSTRUCTION(LT);
			// TELL
			else SET_INSTRUCTION(TELL);

			// OPUŒÆ PISAK
			else SET_INSTRUCTION(PU);
			// PODNIEŒ PISAK
			else SET_INSTRUCTION(PD);
			// POKA¯ ¯Ó£WIA
			else SET_INSTRUCTION(ST);
			// UKRYJ ¯Ó£WIA
			else SET_INSTRUCTION(HT);
			// WYCZYSC EKRAN
			else SET_INSTRUCTION(CS);
			// ERROR lub funkcja
			else
			{
				
				m_list.emplace_back(ErrorCode::UnknownCommand, " nieznana komenda " + current);
			}

			// poprawka, pozwala wychwytywaæ blêdne polecenia gdy wystêpuj¹ jedna po drugiej
			if (currentInstruction.instruction != Instructions::None) {
				if (currentInstruction.instruction != Instructions::TELL)
					status.expectingArg = (int)currentInstruction.instruction & 0x1;
				else
					status.expectingArg = 2;
			}

			// jesli nie spodziewa sie argumentu dodaje go do listy instrukcji
			if (!status.expectingArg) {
				temp_Set.instructions.push_back(currentInstruction);
				currentInstruction = Instruction{ Instructions::None, {0} };
			}
		}
	}

	temp_Set.set_data.repeat = precursor.repeat;
	m_instructionSets.push_back(temp_Set);
}

void Interpreter::getArgList(Instruction& instruction, std::string& string) {
	arglistStripString(string);

	pGetArgList(instruction.arg, string);
}

void Interpreter::arglistStripString(std::string& string) {
	while (string[0] == ' ' || string[0] == '[')
		string.erase(0, 1);

	while (string[string.length() - 1] == ' ' || string[string.length() - 1] == ']'
		|| string[string.length() - 1] == ',')
		string.erase(string.length() - 1);
}

void Interpreter::pGetArgList(std::vector<int>& argList, std::string& string) {
	std::stringstream argStream(string);

	std::string currentArg;
	bool firstArg = true;
	while (std::getline(argStream, currentArg, ',')) {
		// pierwszy argument
		if (firstArg) {
			argList[0] = atoi(currentArg.c_str());
			firstArg = false;
		}
		else
			argList.push_back(atoi(currentArg.c_str()));

	}
}
