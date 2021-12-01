#pragma once

// instrukcje, które wykonuje ¿ó³w
enum class TurtleInstructions : short {
	None = 0xffff,

	// instrukcje nie wymagaj¹ce argumentów
	// ukryj ¿ó³wia
	HT = 0x2,
	// poka¿ ¿ó³wia
	ST = 0x4,
	// podnieœ pisak
	PU = 0x6,
	// opóu
	PD = 0x8,

	// instrukcje wymagaj¹ce argumentu
	// obrót w prawo
	RT = 0x1,
	// obrót w lewo
	LT = 0x3,
	// do przodu
	FD = 0x5,
	// do ty³u
	BK = 0x7
};

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
	Instruction& operator[](int x) { if (x >= 0 && x < instructions.size()) return instructions[x]; return instructions[0]; }
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