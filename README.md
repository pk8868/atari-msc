# atari-msc
ATARI Logo Interpreter
interpreter na motorola science cup

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
    - sfml-audio-s.lib
    - sfml-network-s.lib	
    - opengl32.lib
    - freetype.lib
    - winmm.lib
    - gdi32.lib
    - openal32.lib
    - flac.lib
    - vorbisenc.lib
    - vorbisfile.lib
    - vorbis.lib
    - ogg.lib
    - ws2_32.lib
    - Advapi32.lib
    - shell32.lib
    - Comdlg32.lib