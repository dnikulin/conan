QT       += core gui opengl

TARGET = ConanLive
TEMPLATE = app

DEPENDPATH +=                  \
    ../ConanZero/              \
    ../ConanFile/              \

INCLUDEPATH +=                 \
    ../ConanZero/              \
    ../ConanFile/              \

LIBS +=                        \
    -L../ConanZero/            \
    -L../ConanFile/            \
    -lConanZero                \
    -lConanFile                \
    -lglut                     \

SOURCES +=                     \
    main.cc                    \
    ConanWindow.cc             \
    ConanScreen.cc             \
    ConanScreen-Lines.cc       \
    ConanScreen-Render.cc      \
    ConanScreen-Rotate.cc      \

HEADERS +=                     \
    ConanWindow.hh             \
    ConanScreen.hh             \

FORMS +=                       \
    ConanWindow.ui             \
