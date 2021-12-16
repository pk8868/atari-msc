#pragma once
#include <string>

// kody b��d�w interpretera
enum class ErrorCode : short {
	None = 0xffff,

	// interpreting errors
	ExpectedArgument = 0x01,
	UnknownCommand = 0x04,
	InvalidTurtleID = 0x03,

	// parsing errors
	MissingRightBracket = 0xF1,
	MissingLeftBracket = 0xF2

};

// struktura - kod b��du plus dodatkowa wiadomo��
struct InterpreterError {
	ErrorCode code		= ErrorCode::None;
	std::string message = "";
};

// lista b��d�w
typedef std::vector<InterpreterError> ErrorList;