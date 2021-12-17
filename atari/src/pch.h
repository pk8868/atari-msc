#pragma once
// prekompilowany nag³ówek
// standardowe biblioteki
#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <stdexcept>
#include <string>
#include <memory>
#include <future>

// sfml
#include <SFML/Graphics.hpp>

// imgui
#include "Utils/ImGuiUtils.hpp"

// utils
#include "Utils/Utils.hpp"

// windows.h
#ifdef _WIN32
#include <Windows.h>
#endif

// tealang
#include "tlang/TeaLang.hpp"

// struktury kodu atari
#include "Atari/Interpreter/CodeStructures.hpp"


// monitoring wydajnoœci
#ifdef PERFMON
#include "Utils/PerformanceMonitoring.hpp"
#endif