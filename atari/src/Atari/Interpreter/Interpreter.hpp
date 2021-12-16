#pragma once
#include "CodeStructures.hpp"
#include "Errors.hpp"
#include "Atari/Turtle/Turtle.hpp"

class Interpreter {
	// private interpreter structures
private:
	struct ParsingStatus {
		bool insideRepeat = false;
	};

	struct SetPrecursor {
		std::string code = "";
		int repeat = 1;
	};

	typedef std::vector<SetPrecursor> SetPList;

public:
	Interpreter(std::vector<Turtle>& turtles);
	~Interpreter() { ; }

	ErrorList interpretCode(std::string code);

	void Draw();
private:
	// lista ¿ó³wi
	std::vector<Turtle>& r_turtles;

	// lista zapisanych procedur
	std::vector<Function> m_functions;

	InstructionSets m_instructionSets;

	// interpreter private functions
private:
	void pParse(const std::string& code, SetPList& r_setList, ErrorList& errorList);
	int pGetRepeatNumber(const std::string& code);

	bool ifEmptyString(const std::string& string);

	void pInterpret(SetPrecursor& precursor, ErrorList& errorList);
};