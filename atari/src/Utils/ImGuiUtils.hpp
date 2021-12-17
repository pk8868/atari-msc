#pragma once
#include <imgui/imgui-SFML.h>
#include <imgui/imgui.h>
#include "tlang/TeaLang.hpp"
#include <string>

#define STYLE_BIND_FLOAT(x) if (structure[#x]) t_style.x = structure[#x]->fp32();
#define STYLE_BIND_INT(x) if (structure[#x]) t_style.x = structure[#x]->i32();
#define STYLE_BIND_VECTOR(x) if (structure[#x]) t_style.x = structure[#x]->v2f();
#define STYLE_BIND_COLOR(id) if (structure[#id]) t_style.Colors[id] = structure[#id]->rgba();

namespace util {


	static void changeStyle(tLang::DataStructure& structure) {
		auto& t_style = ImGui::GetStyle();

		// przypisanie nazwy z pliku do struktury
		// zmienne w pliku nazywaja sie tak samo jak zmienne w ImGUIStyle
		STYLE_BIND_FLOAT	(Alpha);
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
		STYLE_BIND_COLOR(ImGuiCol_Text);
		STYLE_BIND_COLOR(ImGuiCol_TextDisabled);
		STYLE_BIND_COLOR(ImGuiCol_WindowBg);
		STYLE_BIND_COLOR(ImGuiCol_ChildBg);
		STYLE_BIND_COLOR(ImGuiCol_PopupBg);
		STYLE_BIND_COLOR(ImGuiCol_Border);
		STYLE_BIND_COLOR(ImGuiCol_BorderShadow);
		STYLE_BIND_COLOR(ImGuiCol_FrameBg);
		STYLE_BIND_COLOR(ImGuiCol_FrameBgHovered);
		STYLE_BIND_COLOR(ImGuiCol_FrameBgActive);
		STYLE_BIND_COLOR(ImGuiCol_TitleBg);
		STYLE_BIND_COLOR(ImGuiCol_TitleBgActive);
		STYLE_BIND_COLOR(ImGuiCol_TitleBgCollapsed);
		STYLE_BIND_COLOR(ImGuiCol_MenuBarBg);
		STYLE_BIND_COLOR(ImGuiCol_ScrollbarBg);
		STYLE_BIND_COLOR(ImGuiCol_ScrollbarGrab);
		STYLE_BIND_COLOR(ImGuiCol_ScrollbarGrabHovered);
		STYLE_BIND_COLOR(ImGuiCol_ScrollbarGrabActive);
		STYLE_BIND_COLOR(ImGuiCol_CheckMark);
		STYLE_BIND_COLOR(ImGuiCol_SliderGrab);
		STYLE_BIND_COLOR(ImGuiCol_SliderGrabActive);
		STYLE_BIND_COLOR(ImGuiCol_Button);
		STYLE_BIND_COLOR(ImGuiCol_ButtonHovered);
		STYLE_BIND_COLOR(ImGuiCol_ButtonActive);
		STYLE_BIND_COLOR(ImGuiCol_Header);
		STYLE_BIND_COLOR(ImGuiCol_HeaderHovered);
		STYLE_BIND_COLOR(ImGuiCol_HeaderActive);
		STYLE_BIND_COLOR(ImGuiCol_Separator);
		STYLE_BIND_COLOR(ImGuiCol_SeparatorHovered);
		STYLE_BIND_COLOR(ImGuiCol_SeparatorActive);
		STYLE_BIND_COLOR(ImGuiCol_ResizeGrip);
		STYLE_BIND_COLOR(ImGuiCol_ResizeGripHovered);
		STYLE_BIND_COLOR(ImGuiCol_ResizeGripActive);
		STYLE_BIND_COLOR(ImGuiCol_Tab);
		STYLE_BIND_COLOR(ImGuiCol_TabHovered);
		STYLE_BIND_COLOR(ImGuiCol_TabActive);
		STYLE_BIND_COLOR(ImGuiCol_TabUnfocused);
		STYLE_BIND_COLOR(ImGuiCol_TabUnfocusedActive);
		STYLE_BIND_COLOR(ImGuiCol_PlotLines);
		STYLE_BIND_COLOR(ImGuiCol_PlotLinesHovered);
		STYLE_BIND_COLOR(ImGuiCol_PlotHistogram);
		STYLE_BIND_COLOR(ImGuiCol_PlotHistogramHovered);
		STYLE_BIND_COLOR(ImGuiCol_TableHeaderBg);
		STYLE_BIND_COLOR(ImGuiCol_TableBorderStrong);
		STYLE_BIND_COLOR(ImGuiCol_TableBorderLight);
		STYLE_BIND_COLOR(ImGuiCol_TableRowBg);
		STYLE_BIND_COLOR(ImGuiCol_TableRowBgAlt);
		STYLE_BIND_COLOR(ImGuiCol_TextSelectedBg);
		STYLE_BIND_COLOR(ImGuiCol_DragDropTarget);
		STYLE_BIND_COLOR(ImGuiCol_NavHighlight);
		STYLE_BIND_COLOR(ImGuiCol_NavWindowingHighlight);
		STYLE_BIND_COLOR(ImGuiCol_NavWindowingDimBg);
		STYLE_BIND_COLOR(ImGuiCol_ModalWindowDimBg);
	}


}