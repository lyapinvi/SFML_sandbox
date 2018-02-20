TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
INCLUDEPATH += "C:/libs/SFML/include/"
LIBS += -L"C:/libs/SFML/bin" -lsfml-window-2 -lsfml-system-2 -lsfml-graphics-2
