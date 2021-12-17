#pragma once
#include "Canvas/Canvas.hpp"
#include "Turtle/Turtle.hpp"
#include "Interpreter/Interpreter.hpp"
#include "Utils/Utils.hpp"
#include <memory>

// z pliku interpreter.hpp
class Interpreter;

// dane aplikacji
struct AppData {
	sf::Vector2i windowSize = { 800, 600 };
};

// klasa atari
class Atari {
public:
	Atari(const AppData& appData);
	~Atari();

	void DrawCanvas(sf::RenderWindow& window);
	void DrawUI();
	void Update();
	
	Interpreter& getInterpreter() { return *m_interpreter; }
	Canvas& getCanvas() { return *m_canvas; }
	const sf::Image& getImage() { return m_canvas->getImage(); }
private:
	// dane aplikacji
	AppData m_appData;

	// instancja interpretera
	std::unique_ptr<Interpreter> m_interpreter = nullptr;

	// lista ¿ó³wii
	std::vector<Turtle> m_turtles;
	std::vector<int>	m_activeTurtles;


	// plansza
	std::unique_ptr<Canvas> m_canvas = nullptr;

	// tekstura
	sf::Texture* m_turtleTexture;


private:
	// aktywny zolw w UI
	int activeTab = 0;
};


static Atari* getAtari(const AppData& appData) {
	return new Atari(appData);
}