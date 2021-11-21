#pragma once
#include <string>

// kody b��d�w interpretera
enum class ErrorCode : short {
	None = 0xffff,

	ExpectedArgument,
	UnknownCommand,
	InvalidTurtleID

};

// struktura - kod b��du plus dodatkowa wiadomo��
struct InterpreterError {
	ErrorCode code		= ErrorCode::None;
	std::string message = "";
};


struct ErrorList {
	std::vector<InterpreterError> errorList;
};