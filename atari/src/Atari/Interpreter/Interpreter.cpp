#include "pch.h"
#include "Interpreter.hpp"
#include "Atari/Atari.hpp"

#define INT_BIND_FUNCTION(x) if (input[i].keyword == #x){\
			tempInstruction.type == Instruction::Type::x;\
			}

Interpreter::Interpreter() {
	;
}

Interpreter& Interpreter::Get()
{
	static Interpreter interpreter;
	return interpreter;
}

void Interpreter::interpretCode(std::string code) {
#ifdef PERFMON
	perf::ScopeClock i_clock("Interpreter");
#endif
	{
		Instruction temp = { Instruction::Type::FD, {"100 * WHO"} };
		std::cout << pValidateArgs(temp);
		code = code.substr(0, code.find('\0'));

		std::vector<Token> t_tokens;
		// zarezerwowanie miejsca (mniej kopiowania)
		t_tokens.reserve(50);
		pTokenize(t_tokens, code);
		t_tokens.shrink_to_fit();

		for (const auto& token : t_tokens) {
			std::cout << token.keyword << ": ";
			for (const auto& arg : token.args) {
				std::cout << arg << ", ";
			}
			std::cout << "\n";
		}

		std::vector<Instruction> t_instructions;

		auto isFunction = pParse(t_instructions, t_tokens);

		for (auto& instruction : t_instructions) {
			if (!pValidateArgs(instruction))
				return;
		}
		// specjalna funkcja do interpretowania funkcji
		if (isFunction) {

		}
		// dodawanie kodu do funkcji
		else if (m_insideFunction) {

		}
		// wykonanie funkcji
		else {

		}


	}
}

void Interpreter::pTokenize(std::vector<Token>& output, std::string& code) {
	std::stringstream stream(code);

	std::vector<std::string> words;

	std::string currentLine;

	while (std::getline(stream, currentLine, ' '))
		words.push_back(currentLine);

	pCombineWords(output, words);
}

void Interpreter::pCombineWords(std::vector<Token>& output, std::vector<std::string>& input) {
	Token currentToken;

	int listCount = 0;

	for (auto& word : input) {
		// poza listami
		if (listCount == 0) {
			// pierwszy lub nowy token
			if (currentToken.keyword == "") 
				currentToken.keyword = word;
			// argument liczbowy
			else if (util::isInt(word) || pSpecial(word))
				currentToken.args.push_back(word);
			// nowy argument
			else {
				// wchodzimy do listy
				if (word[0] == '[') {
					listCount++;

					// jesli jednoargumentowa lista nie dodawaj spacji
					if (word[word.length() - 1] == ']')
						currentToken.args.push_back(word);

					currentToken.args.push_back(word + " ");
				}
				// lub nowy token
				else {
					output.push_back(currentToken);
					currentToken = Token{};
					currentToken.keyword = word;
				}
			}
		}
		else if (listCount > 0) {
			// zawsze dodajemy do ostatniego argumentu
			currentToken.args[currentToken.args.size() - 1] += word;
			// wyjscie z listy
			if (word[word.length() - 1] == ']')
				listCount--;
			// dodanie separatora
			else
				currentToken.args[currentToken.args.size() - 1] += " ";
		}
	}

	if (currentToken.keyword != "")
		output.push_back(currentToken);


}

bool Interpreter::pSpecial(const std::string& string) {
	// argumenty funkcji
	if (string[0] == ':')
		return true;
	if (pIsMathSign(string[0]))
		return true;
	// who
	else if (string.find("WHO") != std::string::npos)
		return true;

	return false;
}

bool Interpreter::pParse(std::vector<Instruction>& output, std::vector<Token>& input) {

	for (int i = 0; i < input.size(); i++) {
		if (input[i].keyword == "TO")
			return true;

		else {
			Instruction tempInstruction{};
			tempInstruction.args = input[i].args;



			if (input[i].keyword == "FD")
				tempInstruction.type = Instruction::Type::FD;
			else if (input[i].keyword == "BK")
				tempInstruction.type = Instruction::Type::BK;
			else if (input[i].keyword == "LT")
				tempInstruction.type = Instruction::Type::LT;
			else if (input[i].keyword == "RT")
				tempInstruction.type = Instruction::Type::RT;
			else if (input[i].keyword == "CS")
				tempInstruction.type = Instruction::Type::CS;
			else if (input[i].keyword == "PU")
				tempInstruction.type = Instruction::Type::PU;
			else if (input[i].keyword == "PD")
				tempInstruction.type = Instruction::Type::PD;
			else if (input[i].keyword == "HT")
				tempInstruction.type = Instruction::Type::HT;
			else if (input[i].keyword == "ST")
				tempInstruction.type = Instruction::Type::ST;
			else if (input[i].keyword == "TELL")
				tempInstruction.type = Instruction::Type::TELL;
			else if (input[i].keyword == "REPEAT")
				tempInstruction.type = Instruction::Type::REPEAT;
			else if (input[i].keyword == "ASK")
				tempInstruction.type = Instruction::Type::ASK;
			else if (input[i].keyword == "SETC")
				tempInstruction.type = Instruction::Type::SETC;
			else if (input[i].keyword == "SETPN")
				tempInstruction.type = Instruction::Type::SETPN;
			else if (input[i].keyword == "SETPC")
				tempInstruction.type = Instruction::Type::SETPC;
			else if (input[i].keyword == "EACH")
				tempInstruction.type = Instruction::Type::EACH;
			else if (input[i].keyword == "POTS")
				tempInstruction.type = Instruction::Type::POTS;
			// else for functions


			if (tempInstruction.type != Instruction::Type::None)
				output.push_back(tempInstruction);
			else
				m_errorList.emplace_back(ErrorCode::UnknownCommand, "Unknown command " + input[i].keyword);
		}
	}

	return false;
}

bool Interpreter::pValidateArgs(Instruction& instruction) {
	if (instruction.type == Instruction::Type::None)
		return false;

	// z jednym argumentem
	if (instruction.type <= Instruction::Type::LT)
		return pValidateOneArgFunction(instruction);
	
	// bez argumentów
	if (instruction.type <= Instruction::Type::PD)
		return pValidateNoArgsFunction(instruction);

	return false;
}

void Interpreter::pRun(std::vector<Instruction>& input) {
	auto& turtles = Atari::Get().getTurtles();
	
	for (const auto& instruction : input) {

		if (instruction.type < Instruction::Type::CS) {
			
		}

	}
}

float Interpreter::evaluate(std::string& string) {
	return 0.0f;
}



