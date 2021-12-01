#pragma once
// MONITOROWANIE HEAP'a ZNACZNIE WP£YWA NA WYDAJNOŒÆ
#ifdef HEAP_MONITOR
// wymagane do funkcji addToFile
#include "PerformanceMonitoring.hpp"


// sta³a wartoœæ bajtów w megabajcie
constexpr float MEGABYTE = 1048576.f;

// zamiana na megabajty (¿eby zapisywanie do pliku by³o bardziej czytelne
static float asMegabytes(const long long& bytes) {
	return float(bytes) / MEGABYTE;
}

// statystyki heap'a
struct HeapStats {
	// automatycznie siê wykona przy wy³¹czaniu programu
	~HeapStats() {
		// zapisywanie danych do pliku
		perf::addToFile(
			"\n===== HEAP =====\n"
			"Calkowita zaalokowana pamiec: "   + std::to_string(asMegabytes(allocatedBytes)) +
			"MB\nCalkowita zwolniona pamiec: " + std::to_string(asMegabytes(freedBytes)) +
			"MB\nMaksymalna uzyta pamiec: "    + std::to_string(asMegabytes(maxBytes)) +
			"MB\n================\n\n");
	}

	void checkIfMax() {
		// nadpisanie maksymalnej liczby alokowaniej pamiêci
		if (getUsedMemory() > maxBytes)
			maxBytes = getUsedMemory();
	}

	// aktualnie u¿ywana pamiêæ
	long long getUsedMemory() {
		return allocatedBytes - freedBytes;
	}

	long long allocatedBytes = 0;
	long long freedBytes = 0;

	long long maxBytes = 0;
};

// globalna instancja statystyk heap'a
HeapStats global_heapStats{};

// nadpisanie operatora new
void* operator new(size_t size) {
	global_heapStats.allocatedBytes += size;

	return malloc(size);
}

// nadpisanie operatora delete
void operator delete(void* data, size_t size) {
	global_heapStats.freedBytes += size;

	free(data);
}

#endif