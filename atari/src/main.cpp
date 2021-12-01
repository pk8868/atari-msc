#include "pch.h"
#include "App/App.hpp"

int main(char** args, int argc) {
	try {
		App app;
		app.run();
	}
	// wypisanie z�apanego b��du do pliku
	catch (std::exception& e)
	{
		util::addToLogFile(e.what());
		return -1;
	}

	return 0;
}