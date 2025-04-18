#pragma once
#include "imgui-SFML.h"
#include <imgui.h>
#include "tlang/TeaLang.hpp"
#include <string>

#include "Utils.hpp"

#define STYLE_BIND_FLOAT(x)		currentVar = structure[#x]; if (currentVar) t_style.x = currentVar->fp32()
#define STYLE_BIND_INT(x)		currentVar = structure[#x]; if (currentVar) t_style.x = currentVar->i32()
#define STYLE_BIND_VECTOR(x)	currentVar = structure[#x]; if (currentVar) t_style.x = currentVar->v2f()
#define STYLE_BIND_COLOR(id)	currentVar = structure["COL_" + std::string(ImGui::GetStyleColorName(id))]; \
								if (currentVar) t_style.Colors[id] = currentVar->rgba();

namespace util {

	static bool setTheme(const std::string& theme) {
		// ustawienie g��wnego motywu kolor�w
		if (theme == "dark")
			ImGui::StyleColorsDark();
		else if (theme == "classic")
			ImGui::StyleColorsClassic();
		else {
			ImGui::StyleColorsLight();
			// jesli jest zla nazwa motywu zwraca false
			if (theme != "light")
				return false;
		}

		return true;
	}

	static void resetStyle() {
		ImGui::GetStyle() = ImGuiStyle();
	}

	static void changeStyle(tLang::DataStructure& structure) {
		auto& t_style = ImGui::GetStyle();	

		// przypisanie nazwy z pliku do struktury
		// zmienne w pliku nazywaja sie tak samo jak zmienne w ImGUIStyle
		tLang::Variable* currentVar;

		STYLE_BIND_FLOAT	(Alpha);
		STYLE_BIND_FLOAT	(DisabledAlpha);
		STYLE_BIND_VECTOR	(WindowPadding);
		STYLE_BIND_FLOAT	(WindowRounding);
		STYLE_BIND_FLOAT	(WindowBorderSize);
		STYLE_BIND_VECTOR	(WindowMinSize);
		STYLE_BIND_VECTOR	(WindowTitleAlign);
		STYLE_BIND_FLOAT	(ChildRounding);
		STYLE_BIND_FLOAT	(ChildBorderSize);
		STYLE_BIND_FLOAT	(PopupRounding);
		STYLE_BIND_FLOAT	(PopupBorderSize);
		STYLE_BIND_VECTOR	(FramePadding);
		STYLE_BIND_FLOAT	(FrameRounding);
		STYLE_BIND_FLOAT	(FrameBorderSize);
		STYLE_BIND_VECTOR	(ItemSpacing);
		STYLE_BIND_VECTOR	(ItemInnerSpacing);
		STYLE_BIND_VECTOR	(CellPadding);
		STYLE_BIND_VECTOR	(TouchExtraPadding);
		STYLE_BIND_FLOAT	(IndentSpacing);
		STYLE_BIND_FLOAT	(ColumnsMinSpacing);
		STYLE_BIND_FLOAT	(ScrollbarSize);
		STYLE_BIND_FLOAT	(ScrollbarRounding);
		STYLE_BIND_FLOAT	(GrabMinSize);
		STYLE_BIND_FLOAT	(GrabRounding);
		STYLE_BIND_FLOAT	(LogSliderDeadzone);
		STYLE_BIND_FLOAT	(TabRounding);
		STYLE_BIND_FLOAT	(TabBorderSize);
		STYLE_BIND_FLOAT	(TabMinWidthForCloseButton);
		STYLE_BIND_VECTOR	(ButtonTextAlign);
		STYLE_BIND_VECTOR	(SelectableTextAlign);
		STYLE_BIND_VECTOR	(DisplayWindowPadding);
		STYLE_BIND_VECTOR	(DisplaySafeAreaPadding);
		STYLE_BIND_FLOAT	(MouseCursorScale);
		STYLE_BIND_INT		(AntiAliasedLines);
		STYLE_BIND_INT		(AntiAliasedLinesUseTex);
		STYLE_BIND_INT		(AntiAliasedFill);
		STYLE_BIND_FLOAT	(CurveTessellationTol);
		STYLE_BIND_FLOAT	(CircleTessellationMaxError);


		// KOLORY
		for (int i = 0; i < 53; i++) {
			STYLE_BIND_COLOR(i);
		}

	}


}