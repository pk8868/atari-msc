#pragma once
#include "Errors.hpp"

class Interpreter {
	// private interpreter structures
public:
	struct Instruction {
		enum class Type {
			None = -1,
			FD, BK,
			RT, LT,

			CS, POTS,
			
			HT, ST,
			PU, PD,

			TELL,
			ASK,
			SETC, SETPN, SETPC,

			EACH,
			REPEAT,


			CUSTOM_FUNCTION,

			TO = 1000, END = 1001
		} type = Type::None;
		std::vector<std::string> args;
	};
#define BIND_COMMAND_STR(x) if (insType == Instruction::Type::x) {return #x;}
	std::string getInstructionString(Instruction::Type insType) {
		BIND_COMMAND_STR(FD);
		BIND_COMMAND_STR(BK);
		BIND_COMMAND_STR(RT);
		BIND_COMMAND_STR(LT);
		BIND_COMMAND_STR(CS);
		BIND_COMMAND_STR(POTS);
		BIND_COMMAND_STR(HT);
		BIND_COMMAND_STR(ST);
		BIND_COMMAND_STR(PU);
		BIND_COMMAND_STR(PD);
		BIND_COMMAND_STR(TELL);
		BIND_COMMAND_STR(ASK);
		BIND_COMMAND_STR(SETC);
		BIND_COMMAND_STR(SETPN);
		BIND_COMMAND_STR(SETPC);
		BIND_COMMAND_STR(EACH);
		BIND_COMMAND_STR(TELL);
		BIND_COMMAND_STR(REPEAT);
		return "Unknown";
	}

	struct Function {
		std::string name;
		std::vector<std::string> argName;

		std::vector<Instruction> instructions;
	};
	

	// no args
	struct ShortInstruction {
		Instruction::Type type = Instruction::Type::None;
	};

	// one arg
	// FD, BK, LT, RT
	struct OneArgInstruction {
		Instruction::Type type = Instruction::Type::None;
		float value;
	};


public:
	Interpreter();
	~Interpreter() { ; }

	// usuniecie kopiowania
	Interpreter(const Interpreter&) = delete;
	void operator=(const Interpreter&) = delete;

	static Interpreter& Get();

	void interpretCode(std::string code);


	const std::string& getErrorString() { return m_errorString; }
	const std::string getInputSymbol() { return m_insideFunction ? ">" : ":"; }
private:
	// do interpretera
	ErrorList m_errorList;
	std::string m_errorString;

	bool m_insideFunction = false;


	std::vector<int> m_activeTurtles{ 0 };

	// lista zapisanych procedur
private:
	// prywatne funkcje interpretera
	struct Token {
		std::string keyword = "";
		std::vector<std::string> args = {};
	};
	
	bool pInterpret(std::string& str, std::vector<Instruction>& output);

	void pTokenize(std::vector<Token>& output, std::string& code);
	void pCombineWords(std::vector<Token>& output, std::vector<std::string>& input);

	// sprawdzenie czy jest to specjalny argument (np. WHO lub argument do funkcji)
	bool pSpecial(const std::string& string);

	bool pParse(std::vector<Instruction>& output, std::vector<Token>& input);

	bool pValidateArgs(Instruction& instruction);

	// validate functions
	// no argument functions
	bool pValidateNoArgsFunction		(const Instruction& instruction);
	// one arg (FD, RT)
	bool pValidateOneArgFunction		(const Instruction& instruction);
	// ASK
	bool pValidateMultipleArgFunction	(const Instruction& instruction);
	// TELL
	bool pValidateTellFunction			(const Instruction& instruction);
	// REPEAT
	bool pValidateRepeatFunction		(const Instruction& instruction);

	bool pIsMathSign(char x);

	void pRun(std::vector<Instruction>& input);

	
	ShortInstruction pGetShortInstruction(Instruction& ins, int who) {
		return { ins.type };
	}
	
	OneArgInstruction pGetOneArgInstruction(Instruction& ins, int who) {
		return { ins.type, evaluate(ins.args[0], who) };
	}

	void executeSimpleCommand(Instruction& instruction);

	float evaluate(std::string& string, int who);

	void pCreateErrorString();

	bool createTurtles(std::vector<int>& ids);

	void getIntList(const std::string& input, std::vector<int>& output);
};