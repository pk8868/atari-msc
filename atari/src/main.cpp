#include "pch.h"
#include "App/App.hpp"

#ifdef HEAP_MONITOR
#include "Utils/HeapMonitoring.hpp"
#endif

int main(char** args, int argc) {
	try {

#ifdef PERFMON
		// wyczyszczenie pliku z danymi wydajnoœci
		perf::init();

		// stworzenie zegara mierzacego czas tworzenia programu
		perf::ScopeClock* init_clock = new perf::ScopeClock("Init clock");
#endif

		App app;

		// zakoñczenie zegara
#ifdef PERFMON
		delete init_clock;
#endif

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