# atari-msc
ATARI Logo Interpreter
Interpreter na motorola science cup
![grafika](https://user-images.githubusercontent.com/87194023/157021840-30df2b21-6e2e-4cc4-818c-283700c2858f.png)

## zależności
SFML >= 2.5.1

## budowanie
- C++ 20
- nagłówek prekompilowany pch.h
    - używany dla wszystkich plików z wyjątkiem plików w katalogu imgui/ i tlang/
- definicje preprocesora
    - SFML_STATIC
- biblioteki statyczne (release):
    - sfml-graphics-s.lib
    - sfml-window-s.lib
    - sfml-system-s.lib
    - freetype.lib
    - opengl32.lib
    - winmm.lib
    - gdi32.lib
    - ws2_32.lib
    - Advapi32.lib
    - shell32.lib
    - Comdlg32.lib
- dodatkowe katalogi #include
    - src/
    - src/imgui/
- i wszystko potrzebne z sfml - https://www.sfml-dev.org/tutorials/2.5/#getting-started 
