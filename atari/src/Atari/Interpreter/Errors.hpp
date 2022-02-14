#pragma once
#include <string>

// kody b��d�w interpretera
enum class ErrorCode : short {
	None = -1,

	ExpectedArgument = 1,
	ExpectedNumber,
	UnknownCommand,
	InvalidTurtleID,
	InvalidExpression,
	Unimplemented,
	TooManyArgs,

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