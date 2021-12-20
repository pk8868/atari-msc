#pragma once
#include "CodeStructures.hpp"
#include "Errors.hpp"
#include "Atari/Turtle/Turtle.hpp"

class Interpreter {
	// private interpreter structures
private:
	struct ParsingStatus {
		bool insideSpecialCommand = false;
		enum SpecialCommand {
			Repeat,
			Ask
		} specialCommand;
	};

	struct SetPrecursor {
		std::string code = "";
		int repeat = 1;
	};

	typedef std::vector<SetPrecursor> SetPList;

public:
	struct TurtleAddData {
		sf::Texture* turtleptr;
	};

	Interpreter(std::vector<Turtle>& turtles, Canvas& r_canvas, const TurtleAddData& data);
	~Interpreter() { ; }

	ErrorList interpretCode(std::string code);

	const std::string& getErrorString() { return m_errorString; }
private:
	// referencja canvasa
	Canvas& r_canvas;

	// do interpretera
	ErrorList m_list;
	std::string m_errorString;


	// lista ��wi
	std::vector<Turtle>& r_turtles;
	std::vector<int> m_activeTurtles{ 0 };

	// tekstura zolwia
	TurtleAddData pAddData;

	// lista zapisanych procedur
	std::vector<Function> m_functions;

	InstructionSets m_instructionSets;

	// interpreter private functions
private:
	void pParse(const std::string& code, SetPList& r_setList);
	int pGetRepeatNumber(const std::string& code);

	bool ifEmptyString(const std::string& string);

	void pInterpret(SetPrecursor& precursor);

private:
	void getArgList(Instruction& instruction, std::string& string);
	void arglistStripString(std::string& string);
	void pGetArgList(std::vector<int>& argList, std::string& string);

private:
	void pCreateErrorString();
	void pDeleteSpaces(std::string& string);

private:
	void markInactiveTurtles();
};