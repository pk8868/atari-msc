#pragma once
#include <string>

// kody b��d�w interpretera
enum class ErrorCode : short {
	None = -1,

	// interpreting errors
	ExpectedArgument = 1,
	UnknownCommand,
	InvalidTurtleID,

	// parsing errors
	MissingLeftBracket = 0xF1,
	MissingRightBracket

};

// struktura - kod b��du plus dodatkowa wiadomo��
struct InterpreterError {
	ErrorCode code		= ErrorCode::None;
	std::string message = "";
};

// lista b��d�w
typedef std::vector<InterpreterError> ErrorList;