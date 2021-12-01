#pragma once
#ifdef PERFMON
#include <chrono>
#include <fstream>
#include <iostream>

#define PERFMONITOR_FILE "perflog.txt"

namespace perf {
	// wyczyszczenie dawnego pliku z danymi
	static void init() {
		// wyczyszczenie pliku
		std::ofstream stream(PERFMONITOR_FILE, std::ios::out, std::ios::trunc);
		stream.close();
	}


	// dopisanie do pliku
	static void addToFile(const std::string& string) {
		std::ofstream stream(PERFMONITOR_FILE, std::ios::out | std::ios::app);

		if (stream.good()) {
			stream << string << std::endl;
		}
		else {
			std::cerr << "Couldn't open log.txt\n";
		}

		stream.close();
	}

	/// zegar automatycznie wy³¹czajacy sie po usuniêciu, nazwa powinna byæ krótsza ni¿ 16 znaków
	class ScopeClock {
	public:
		ScopeClock(const std::string& clockName)
			:m_clockName(clockName)
		{
			// pobranie czasu rozpoczêcia
			m_startPoint = std::chrono::high_resolution_clock::now();
		}
		~ScopeClock() {
			// pobranie czasu zakoñczenia
			auto temp_endPoint = std::chrono::high_resolution_clock::now();

			// konwersja na long long
			auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_startPoint).time_since_epoch().count();
			auto end = std::chrono::time_point_cast<std::chrono::milliseconds>(temp_endPoint).time_since_epoch().count();

			perf::addToFile(m_clockName + ": " +
				std::to_string(end - start) + "ms");
		}
	private:
		std::string m_clockName;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startPoint;
	};
}
#endif

