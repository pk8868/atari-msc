#pragma once
#include "Canvas/Canvas.hpp"
#include "Turtle/Turtle.hpp"
#include "Interpreter/Interpreter.hpp"

class Atari {
public:
	Atari();
	~Atari();

	void Draw(sf::RenderWindow& window);
	void Update();

	
	Interpreter& getInterpreter() { return m_interpreter; }
private:
	// instancja interpretera
	Interpreter m_interpreter;

	// lista ¿ó³wii
	std::vector<Turtle> m_turtles;
	std::vector<int>	m_activeTurtles;


	// plansza
	Canvas m_canvas;

};