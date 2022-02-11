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
		} type;
		std::vector<std::string> args;
	};

	struct Function {
		std::string name;
		std::vector<std::string> argName;

		std::vector<Instruction> instructions;
	};
	

	// no args
	struct ShortInstruction {
		Instruction::Type type;
	};

	// one arg
	// FD, BK, LT, RT
	struct OneArgInstruction {
		Instruction::Type type;
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
	// TELL, ASK
	bool pValidateMultipleArgFunction	(const Instruction& instruction);
	// CUSTOM FUNCTION
	bool pValidateFunctionArgFunction	(const Instruction& instruction);
	// REPEAT
	bool pValidateRepeatFunction		(const Instruction& instruction);

	bool pIsMathSign(char x);

	void pRun(std::vector<Instruction>& input);
	
	template <class T>
	T pGet(Instruction& instruction) { return T(); }

	template<>
	ShortInstruction pGet<ShortInstruction>(Instruction& ins) {
		return { ins.type };
	}
	
	template<>
	OneArgInstruction pGet<OneArgInstruction>(Instruction& ins) {
		return { ins.type, evaluate(ins.args[0]) };
	}

	float evaluate(std::string& string);
};