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
	m_errorList.clear();
	std::vector<Instruction> instructions;
	code = code.substr(0, code.find('\0'));
	bool OK = pInterpret(code, instructions);
	if (OK)
		pRun(instructions);
	pCreateErrorString();
}

void Interpreter::pCreateErrorString() {
	m_errorString.clear();
	std::stringstream stream;
	for (int i = 0; i < m_errorList.size(); i++)
		stream << (int)m_errorList[i].code << " - " << m_errorList[i].message << "\n";

	m_errorString = stream.str();
}

bool Interpreter::createTurtles(std::vector<int>& ids) {
	auto& turtles = Atari::Get().getTurtles();
	for (auto& id : ids) {
		if (id > turtles.size()) {
			m_errorList.emplace_back(ErrorCode::InvalidTurtleID, "Too high Turtle ID");
			return false;
		}
		else if (id == turtles.size())
			turtles.push_back(Turtle{});
	}

	return true;
}

void Interpreter::getIntList(const std::string& input, std::vector<int>& output) {
	std::stringstream strStr(input);
	std::string number;
	while (std::getline(strStr, number, ' '))
		output.push_back(atoi(number.c_str()));
}

bool Interpreter::pInterpret(std::string& str, std::vector<Instruction>& output) {
#ifdef PERFMON
	perf::ScopeClock i_clock("Interpreter");
#endif
	{
		std::vector<Token> t_tokens;
		// zarezerwowanie miejsca (mniej kopiowania)
		t_tokens.reserve(50);
		pTokenize(t_tokens, str);
		t_tokens.shrink_to_fit();

		auto isFunction = pParse(output, t_tokens);

		for (auto& instruction : output)
			pValidateArgs(instruction);

		if (m_errorList.size() != 0)
			return false;
	}
	return true;
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
					// jesli jednoargumentowa lista nie dodawaj spacji
					if (word[word.length() - 1] == ']')
						currentToken.args.push_back(word);
					else {
						currentToken.args.push_back(word + " ");
						listCount++;
					}
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

	while (listCount > 0) {
		m_errorList.emplace_back(ErrorCode::MissingRightBracket, "Missing right bracket");
		listCount--;
	}
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
			return false;

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
	
	if (instruction.type == Instruction::Type::REPEAT)
		return pValidateRepeatFunction(instruction);

	if (instruction.type == Instruction::Type::ASK)
		return pValidateMultipleArgFunction(instruction);

	if (instruction.type == Instruction::Type::TELL)
		return pValidateTellFunction(instruction);

	return false;
}

void Interpreter::pRun(std::vector<Instruction>& input) {	
	for (auto& instruction : input) {
		if (instruction.type == Instruction::Type::CS) {
			Canvas::Get().Clear();
		}
		else if (instruction.type == Instruction::Type::REPEAT) {
			int repeats = atoi(instruction.args[0].c_str());

			std::vector<Instruction> repeatInstructions;
			auto input = instruction.args[1].substr(1U, instruction.args[1].rfind(']') - 1);
			bool OK = pInterpret(input, repeatInstructions);
			if (OK) {
				for (int i = 0; i < repeats; i++)
					pRun(repeatInstructions);
			}
		}
		else if (instruction.type == Instruction::Type::TELL) {
			std::vector<int> newTurtles;
			// lista
			if (instruction.args[0][0] == '[')
				getIntList(instruction.args[0].substr(1U, instruction.args[0].rfind(']') - 1)
					, newTurtles);
			else
				newTurtles.push_back(atoi(instruction.args[0].c_str()));
			if (!createTurtles(newTurtles))
				return;
			m_activeTurtles = newTurtles;
			Atari::Get().UpdateActiveTurtles(m_activeTurtles);
		}
		else if (instruction.type == Instruction::Type::ASK) {
			std::vector<Instruction> tellInstructions;
			auto input = instruction.args[1].substr(1U, instruction.args[1].rfind(']') - 1);
			bool OK = pInterpret(input, tellInstructions);

			std::vector<int> oldTurtles = m_activeTurtles;
			std::vector<int> newTurtles;

			// lista
			if (instruction.args[0][0] == '[')
				getIntList(instruction.args[0].substr(1U, instruction.args[0].rfind(']') - 1), newTurtles);
			else
				newTurtles.push_back(atoi(instruction.args[0].c_str()));

			if (!createTurtles(newTurtles))
				return;

			m_activeTurtles = newTurtles;
			if (OK)
				pRun(tellInstructions);
			m_activeTurtles = oldTurtles;
		}
		else {
			executeSimpleCommand(instruction);
		}
	}
}

void Interpreter::executeSimpleCommand(Instruction& instruction) {
	auto& turtles = Atari::Get().getTurtles();
	for (auto& turtleID : m_activeTurtles) {
		if (instruction.type <= Instruction::Type::CS) {
			auto exec = pGet<OneArgInstruction>(instruction, turtleID);
			turtles[turtleID].Run(exec);
		}
		else if (instruction.type >= Instruction::Type::HT && instruction.type <= Instruction::Type::PD) {
			auto exec = pGet<ShortInstruction>(instruction, turtleID);
			turtles[turtleID].Run(exec);
		}
		else {
			m_errorList.emplace_back(ErrorCode::Unimplemented, "Unimplemented command");
		}
	}
}

float Interpreter::evaluate(std::string& string, int who) {
	return (float)atof(string.c_str());
}



