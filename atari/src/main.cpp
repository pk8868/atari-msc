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

#ifdef HEAP_MONITOR
		bool running = true;

		std::future<void> snapshotHandlerThread;
		snapshotHandlerThread = std::async(std::launch::async, runSnapshotHandler, &running);
#endif // HEAP_MONITOR


		app.run();

#ifdef HEAP_MONITOR
		running = false;
		snapshotHandlerThread.get();
#endif
	}
	// wypisanie z³apanego b³êdu do pliku
	catch (std::exception& e)
	{
		util::addToLogFile(e.what());
		return -1;
	}


	return 0;
}