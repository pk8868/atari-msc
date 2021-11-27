#include "pch.h"
#include "App/App.hpp"

int main(char** args, int argc) {
	try {
		App app;
		app.run();
	}
	// wypisanie z�apanego b��du
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}