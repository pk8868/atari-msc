#pragma once
#include "Interpreter/Interpreter.hpp"
#include "Turtle/Turtle.hpp"
#include "Canvas/Canvas.hpp"
#include "Utils/Utils.hpp"
#include <memory>

// z pliku interpreter.hpp
class Interpreter;

// klasa atari
class Atari {
public:
	Atari();
	~Atari();

	static Atari& Get();

	// usuniecie kopiowania
	Atari(const Atari&) = delete;
	void operator=(const Atari&) = delete;

	void DrawCanvas(sf::RenderWindow& window);
	void DrawUI();
	void Update();
	
	void UpdateActiveTurtles(std::vector<int>& activeTurtles);

	const sf::Image getImage() { return Canvas::Get().getImage(); }
	const sf::Texture* getTexture() { return m_turtleTexture; }
	std::vector<Turtle>& getTurtles() { return m_turtles; }
private:
	// lista ��wii
	std::vector<Turtle> m_turtles;

	// tekstura
	sf::Texture* m_turtleTexture = nullptr;


private:
	// aktywny zolw w UI
	int activeTab = 0;
};