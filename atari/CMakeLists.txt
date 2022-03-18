set(PROJECT_NAME atari)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "resource.h"
    "src/App/App.cpp"
    "src/App/App.hpp"
    "src/App/Logger/ErrorLog.cpp"
    "src/App/Logger/ErrorLog.hpp"
    "src/App/Run.cpp"
    "src/Atari/Atari.cpp"
    "src/Atari/Atari.hpp"
    "src/Atari/Canvas/Canvas.cpp"
    "src/Atari/Canvas/Canvas.hpp"
    "src/Atari/Interpreter/Errors.hpp"
    "src/Atari/Interpreter/Interpreter.cpp"
    "src/Atari/Interpreter/Interpreter.hpp"
    "src/Atari/Interpreter/Validation.cpp"
    "src/Atari/Turtle/Turtle.cpp"
    "src/Atari/Turtle/Turtle.hpp"
    "src/imgui/imconfig.h"
    "src/imgui/imgui-SFML.cpp"
    "src/imgui/imgui-SFML.h"
    "src/imgui/imgui-SFML_export.h"
    "src/imgui/imgui.cpp"
    "src/imgui/imgui.h"
    "src/imgui/imgui_draw.cpp"
    "src/imgui/imgui_internal.h"
    "src/imgui/imgui_tables.cpp"
    "src/imgui/imgui_widgets.cpp"
    "src/imgui/imstb_rectpack.h"
    "src/imgui/imstb_textedit.h"
    "src/imgui/imstb_truetype.h"
    "src/Input/Input.cpp"
    "src/Input/Input.hpp"
    "src/main.cpp"
    "src/pch.cpp"
    "src/pch.h"
    "src/tlang/dataStructure.cpp"
    "src/tlang/tCode.cpp"
    "src/tlang/tCodeInterpreter.cpp"
    "src/tlang/TeaLang.hpp"
    "src/tlang/Variable.cpp"
    "src/Utils/HeapMonitoring.hpp"
    "src/Utils/ImGuiUtils.hpp"
    "src/Utils/PerformanceMonitoring.hpp"
    "src/Utils/Utils.hpp"
)
source_group("" FILES ${no_group_source_files})

set(ALL_FILES
    ${no_group_source_files}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE textEditor)

################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DPERFORMANCEMONITOR "${PROJECT_NAME}-perf-d"
    TARGET_NAME_RPERFORMANCEMONITOR "${PROJECT_NAME}-perf"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG               "${CMAKE_SOURCE_DIR}/bin-debug/"
    OUTPUT_DIRECTORY_DPERFORMANCEMONITOR "${CMAKE_SOURCE_DIR}/PerformanceDebug/"
    OUTPUT_DIRECTORY_RELEASE             "${CMAKE_SOURCE_DIR}/bin/"
    OUTPUT_DIRECTORY_RPERFORMANCEMONITOR "${CMAKE_SOURCE_DIR}/PerformanceRelease/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE             "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_RPERFORMANCEMONITOR "TRUE"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/imgui;"
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/SFML-x64/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:DPerformanceMonitor>:"
        "PERFMON;"
        "HEAP_MONITOR;"
        "HEAP__DEBUG;"
        "%(PreprocessorDefinitions)SFML_STATIC;"
        ""
    ">"
    "$<$<CONFIG:RPerformanceMonitor>:"
        "PERFMON;"
        "HEAP_MONITOR;"
        "HEAP_NDEBUG;"
        "%(PreprocessorDefinitions)SFML_STATIC;"
        ""
    ">"
    "SFML_STATIC;"
    "IMGUI_DISABLE_OBSOLETE_FUNCTIONS;"
    "_CONSOLE;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /fp:precise
        >
        $<$<CONFIG:DPerformanceMonitor>:
            /fp:fast
        >
        $<$<CONFIG:Release>:
            /Od;
            /Oi-;
            /GT;
            /Gy;
            /Ot;
            /fp:precise;
            /guard:cf
        >
        $<$<CONFIG:RPerformanceMonitor>:
            /Oi;
            /GT;
            /Gy;
            /Ot;
            /fp:fast;
            /guard:cf
        >
        /permissive-;
        /MP;
        /sdl;
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(src/imgui/imgui-SFML.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(src/imgui/imgui.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(src/imgui/imgui_draw.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(src/imgui/imgui_tables.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(src/imgui/imgui_widgets.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(src/tlang/dataStructure.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(src/tlang/tCode.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(src/tlang/tCodeInterpreter.cpp ${FILE_CL_OPTIONS})
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(src/tlang/Variable.cpp ${FILE_CL_OPTIONS})
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /DEBUG;
            /SUBSYSTEM:CONSOLE;
            /INCREMENTAL
        >
        $<$<CONFIG:DPerformanceMonitor>:
            /DEBUG;
            /SUBSYSTEM:CONSOLE;
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /SUBSYSTEM:WINDOWS;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO;
            /ENTRY:"mainCRTStartup"
        >
        $<$<CONFIG:RPerformanceMonitor>:
            /SUBSYSTEM:WINDOWS;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO;
            /ENTRY:"mainCRTStartup"
        >
    )
endif()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "$<$<CONFIG:Debug>:"
        "sfml-graphics-s-d;"
        "sfml-window-s-d;"
        "sfml-system-s-d;"
        "sfml-audio-s-d;"
        "sfml-network-s-d.lib;"
        "openal32;"
        "flac;"
        "vorbisenc;"
        "vorbisfile;"
        "vorbis;"
        "ogg"
    ">"
    "$<$<CONFIG:DPerformanceMonitor>:"
        "sfml-graphics-s-d;"
        "sfml-window-s-d;"
        "sfml-system-s-d;"
        "sfml-audio-s-d;"
        "sfml-network-s-d.lib;"
        "openal32;"
        "flac;"
        "vorbisenc;"
        "vorbisfile;"
        "vorbis;"
        "ogg"
    ">"
    "$<$<CONFIG:Release>:"
        "sfml-graphics-s;"
        "sfml-window-s;"
        "sfml-system-s"
    ">"
    "$<$<CONFIG:RPerformanceMonitor>:"
        "sfml-graphics-s;"
        "sfml-window-s;"
        "sfml-system-s;"
        "sfml-audio-s;"
        "sfml-network-s.lib;"
        "openal32;"
        "flac;"
        "vorbisenc;"
        "vorbisfile;"
        "vorbis;"
        "ogg"
    ">"
    "freetype;"
    "opengl32;"
    "winmm;"
    "gdi32;"
    "ws2_32;"
    "Advapi32;"
    "shell32;"
    "Comdlg32"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/SFML-x64/lib"
)

