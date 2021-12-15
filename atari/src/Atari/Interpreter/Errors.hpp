#pragma once
#include <string>

// kody b³êdów interpretera
enum class ErrorCode : short {
	None = 0xffff,

	ExpectedArgument,
	UnknownCommand,
	InvalidTurtleID

};

// struktura - kod b³êdu plus dodatkowa wiadomoœæ
struct InterpreterError {
	ErrorCode code		= ErrorCode::None;
	std::string message = "";
};


struct ErrorList {
	std::vector<InterpreterError> errorList;
};