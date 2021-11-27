#pragma once
#include "CodeStructures.hpp"
#include "Errors.hpp"
#include "Atari/Turtle/Turtle.hpp"

class Interpreter {
public:
	Interpreter(std::vector<Turtle>& turtles);
	~Interpreter() { ; }

private:
	// lista ¿ó³wi
	std::vector<Turtle>& r_turtles;

	// lista zapisanych procedur
	std::vector<Function> m_functions;

};