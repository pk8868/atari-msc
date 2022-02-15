#include "pch.h"
#include "Interpreter.hpp"
#include "Atari/Atari.hpp"

enum Traits_ {
	T_NONE,
	T_ERROR,
	T_EQSIGN,
	T_NUMBER,
	T_SPECIALWORD,
	T_FUNCTION_ARG
};
typedef uint8_t Traits;

struct ExpressionTrait {
	std::vector<Traits> traits;
};

static bool isInt(const std::string& string) {
	for (int i = 0; i < string.length(); i++) {
		if (!std::isdigit(string[i])) {
			return false;
		}
	}
	return true;
}

bool isMathSign(char a) {
	return (a == '+') || (a == '-') || (a == '*') || (a == '/');
}

static Traits getTrait(const std::string& string) {
	if (isInt(string))
		return T_NUMBER;

	if (string == "WHO")
		return T_SPECIALWORD;

	if (string[0] == ':') {
		// sprawdzic czy jest argumentem funkcji

		return T_FUNCTION_ARG;
	}

	return T_ERROR;
}

static ExpressionTrait getTraits(const std::string& string) {
	ExpressionTrait trait;
	std::string buffer = "";

	for (auto a : string) {
		if (a == ' ' || a == '\t')
			continue;
		if (isMathSign(a)) {
			trait.traits.push_back(getTrait(buffer)); // wyrazenie przed znakiem
			trait.traits.push_back(T_EQSIGN);
			buffer = "";
			continue;
		}
		buffer += a;
	}
	trait.traits.push_back(getTrait(buffer));

	return trait;
}

static bool validateTraits(const ExpressionTrait& trait) {
	for (auto& currentTrait : trait.traits) {
		if (currentTrait == T_ERROR)
			return false;
	}
	return true;
}
// validation types

bool Interpreter::pValidateNoArgsFunction(const Instruction& instruction) {
	if (instruction.args.size())
		m_errorList.emplace_back(ErrorCode::TooManyArgs, "Too many args");
	return instruction.args.size() == 0;
}

bool Interpreter::pValidateOneArgFunction(const Instruction& instruction) {
	if (instruction.args.size() > 1)
		m_errorList.emplace_back(ErrorCode::TooManyArgs, "Too many args");
	else if (instruction.args.size() == 0)
		m_errorList.emplace_back(ErrorCode::ExpectedArgument, "Expected argument");
	if (instruction.args.size() != 1)
		return false;

	auto x = getTraits(instruction.args[0]);

	if (!validateTraits(x)) {
		m_errorList.emplace_back(ErrorCode::InvalidExpression, "Invalid expression");
		return false; // jeœli ma ceche "error"
	}
	return true;
}

bool Interpreter::pValidateRepeatFunction(const Instruction& instruction) {
	if (instruction.args.size() > 2)
		m_errorList.emplace_back(ErrorCode::TooManyArgs, "Too many args");
	else if (instruction.args.size() < 2)
		m_errorList.emplace_back(ErrorCode::ExpectedArgument, "Expected argument");
	if (instruction.args.size() != 2)
		return false;

	auto x = getTraits(instruction.args[0]);

	if (!validateTraits(x)) {
		m_errorList.emplace_back(ErrorCode::InvalidExpression, "Invalid expression");
		return false; // jeœli ma ceche "error"
	}

	auto& code = instruction.args[1];
	auto input = code.substr(1U, code.rfind(']') - 1U);
	std::vector<Instruction> instructions;
	return pInterpret(input, instructions);
}

bool Interpreter::pIsMathSign(char x) {
	return isMathSign(x);
}
