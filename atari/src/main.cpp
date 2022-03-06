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
#endif

#ifdef HEAP_MONITOR
		bool running = true;

		std::future<void> snapshotHandlerThread;
		snapshotHandlerThread = std::async(std::launch::async, runSnapshotHandler, &running);
#endif // HEAP_MONITOR

		App::Get().run();

#ifdef HEAP_MONITOR
		running = false;
		snapshotHandlerThread.get();
#endif

	}
	// wypisanie z³apanego b³êdu do pliku
	catch (std::exception& e)
	{

#if _WIN32
		// okno errora windows
		MessageBoxA(NULL, e.what(), NULL, MB_OK | MB_ICONERROR);
#endif

		return -1;
	}


	return 0;
}