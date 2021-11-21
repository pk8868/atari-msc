#pragma once
#include "Atari/Atari.hpp"

// instrukcja dla ¿ó³wia
struct Instruction {
	// kod instrukcji
	TurtleInstructions instruction = TurtleInstructions::None;

	// argument
	short arg = 0;
};

// zestaw instrukcji, zapisywany w nawiasach kwadratowych
struct InstructionSet {
	// operator []
	Instruction& operator[](int x) { if (x >= 0 && x < instructions.size()) return instructions[x]; }
	int size() { return (int)instructions.size(); }

	// lista instrukcji
	std::vector<Instruction> instructions;

	// dodatkowe informacje na temat zestawu instrukcji
	struct setData {
		// iloœæ powtórzeñ
		int repeat = 1;

	} set_data;
};

// funkcja
struct Function {
	InstructionSet m_set;

	// funkcja
	struct functionData {
		// identyfikator funkcji
		std::string name = "";

		// flaga, czy funkcja wymaga dodatkowego argumentu
		bool req_Arg = false;

	} f_data;
};