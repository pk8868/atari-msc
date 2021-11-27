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
#include <imgui/imgui-SFML.h>
#include <imgui/imgui.h>

// windows.h
#ifdef _WIN32
#include <Windows.h>
#endif

// tealang
#include "tlang/TeaLang.hpp"

// struktury kodu atari
#include "Atari/Interpreter/CodeStructures.hpp"