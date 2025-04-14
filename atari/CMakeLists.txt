add_subdirectory("dependencies")


file(GLOB_RECURSE ATARI_SOURCE
    "*.hpp"
    "*.h"
    "*.cpp"
)

add_executable(${PROJECT_NAME}
    ${ATARI_SOURCE}
)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} PRIVATE "src/" ${SFML_INCLUDE_DIR} ${IMGUI_DIR} ${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML sfml-system sfml-window sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_precompile_headers(${PROJECT_NAME} PRIVATE "src/pch.h")

file(COPY "./assets" DESTINATION ${CMAKE_BINARY_DIR}/bin)
