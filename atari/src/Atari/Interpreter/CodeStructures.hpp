#pragma once

// instrukcje, kt�re wykonuje ��w
enum class TurtleInstructions : short {
	None = 0xffff,

	// instrukcje nie wymagaj�ce argument�w
	// ukryj ��wia
	HT = 0x2,
	// poka� ��wia
	ST = 0x4,
	// podnie� pisak
	PU = 0x6,
	// op�u
	PD = 0x8,

	// instrukcje wymagaj�ce argumentu
	// obr�t w prawo
	RT = 0x1,
	// obr�t w lewo
	LT = 0x3,
	// do przodu
	FD = 0x5,
	// do ty�u
	BK = 0x7
};

// instrukcja dla ��wia
struct Instruction {
	// kod instrukcji
	TurtleInstructions instruction = TurtleInstructions::None;

	// argument
	short arg = 0;
};

// zestaw instrukcji, zapisywany w nawiasach kwadratowych
struct InstructionSet {
	// operator []
	Instruction& operator[](int x) { if (x >= 0 && x < instructions.size()) return instructions[x]; return instructions[0]; }
	int size() { return (int)instructions.size(); }

	// lista instrukcji
	std::vector<Instruction> instructions;

	// dodatkowe informacje na temat zestawu instrukcji
	struct setData {
		// ilo�� powt�rze�
		int repeat = 1;

	} set_data;
};

// funkcja
struct Function {
	std::vector<InstructionSet> m_sets;

	// funkcja
	struct functionData {
		// identyfikator funkcji
		std::string name = "";

		// flaga, czy funkcja wymaga dodatkowego argumentu
		bool req_Arg = false;
		std::string argName = "";
	} f_data;
};