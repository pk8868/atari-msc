#pragma once
#include <string>

// kody b³êdów interpretera
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

// struktura - kod b³êdu plus dodatkowa wiadomoœæ
struct InterpreterError {
	ErrorCode code		= ErrorCode::None;
	std::string message = "";
};

// lista b³êdów
typedef std::vector<InterpreterError> ErrorList;