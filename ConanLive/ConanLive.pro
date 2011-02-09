QT       += core gui opengl

TARGET = ConanLive
TEMPLATE = app

DESTDIR = ../Release/

DEPENDPATH +=                  \
    ../ConanZero/              \
    ../ConanFile/              \

INCLUDEPATH +=                 \
    ../ConanZero/              \
    ../ConanFile/              \

LIBS +=                        \
    -L../Release/              \
    -lConanZero                \
    -lConanFile                \

SOURCES +=                     \
    main.cc                    \
    ConanWindow.cc             \
    ConanScreen.cc             \
    ConanScreen-Lines.cc       \
    ConanScreen-Panes.cc       \
    ConanScreen-Render.cc      \
    ConanScreen-Rotate.cc      \

HEADERS +=                     \
    ConanWindow.hh             \
    ConanScreen.hh             \
    ConanLivePlugin.hh         \

FORMS +=                       \
    ConanWindow.ui             \
