#pragma once
// MONITOROWANIE HEAP'a ZNACZNIE WP�YWA NA WYDAJNO��
#ifdef HEAP_MONITOR
// wymagane do funkcji addToFile
#include "PerformanceMonitoring.hpp"
#include "Utils.hpp"


// sta�a warto�� bajt�w w megabajcie
constexpr float MEGABYTE = 1048576.f;

// zamiana na megabajty (�eby zapisywanie do pliku by�o bardziej czytelne
static float asMegabytes(const long long& bytes) {
	return float(bytes) / MEGABYTE;
}

// migawka stanu heap'a
struct HeapSnapshot {
	std::string getString();
	HeapSnapshot();

	std::string time;
	long long usedMemory = 0;
};

// statystyki heap'a
struct HeapStats {
	HeapStats() {
		snapshots.reserve(10);
	}
	// automatycznie si� wykona przy wy��czaniu programu
	~HeapStats() {
		std::stringstream stream;

		// zapisywanie danych do pliku
		stream << "\n===== HEAP =====\n";
		stream << "Calkowita zaalokowana pamiec: ";
		stream << std::to_string(asMegabytes(allocatedBytes));
		stream << "MB\nCalkowita zwolniona pamiec: ";
		stream << std::to_string(asMegabytes(freedBytes));
		stream << "MB\nMaksymalna uzyta pamiec: ";
		stream << std::to_string(asMegabytes(maxBytes));
		stream << "MB\n = SNAPSHOTS =\n";

		for (int i = 0; i < snapshots.size(); i++)
			stream << snapshots[i].getString();


		stream << "===== HEAP =====\n";

		// zapisanie snapshot�w do pliku
		perf::addToFile(stream.str());
	}

	void checkIfMax() {
		// nadpisanie maksymalnej liczby alokowaniej pami�ci
		if (getUsedMemory() > maxBytes)
			maxBytes = getUsedMemory();
	}

	// aktualnie u�ywana pami��
	long long getUsedMemory() {
		return allocatedBytes - freedBytes;
	}

	void createSnapshot() {
		// dodanie snapshota na koniec listy
		snapshots.emplace_back();
	}

	long long allocatedBytes = 0;
	long long freedBytes = 0;

	long long maxBytes = 0;

	// migawki
	std::vector<HeapSnapshot> snapshots;
};

// globalna instancja statystyk heap'a
HeapStats global_heapStats{};

// nadpisanie operatora new
void* operator new(size_t size) {
	global_heapStats.allocatedBytes += size;

	global_heapStats.checkIfMax();

	return malloc(size);
}

// nadpisanie operatora delete
void operator delete(void* data, size_t size) {
	global_heapStats.freedBytes += size;

	free(data);
}

// migawka stanu heap'a
HeapSnapshot::HeapSnapshot() {
	usedMemory = global_heapStats.getUsedMemory();
	time = util::getShortTime();
}

std::string HeapSnapshot::getString() {
	return time + ": " + std::to_string(asMegabytes(usedMemory)) + "MB\n";
}


// snapshot handler
static void runSnapshotHandler(bool* running) {
	while (*running) {
		// je�li naci�ni�ty jest klawisz f7, zr�b migawk� heapa
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F7)) {
			global_heapStats.createSnapshot();

			// pauza na 100 ms
			Sleep(100);
		}
	}
}

#endif