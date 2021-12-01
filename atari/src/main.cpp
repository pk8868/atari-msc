#include "pch.h"
#include "App/App.hpp"

int main(char** args, int argc) {
	try {
		App app;
		app.run();
	}
	// wypisanie z³apanego b³êdu do pliku
	catch (std::exception& e)
	{
		util::addToLogFile(e.what());
		return -1;
	}

	return 0;
}