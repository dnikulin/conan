#-------------------------------------------------
#
# Project created by QtCreator 2011-02-02T18:49:25
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = ConanLive
TEMPLATE = app

DEPENDPATH +=                  \
    ../ConanZero/              \

INCLUDEPATH +=                 \
    ../ConanZero/              \

LIBS +=                        \
    -L../ConanZero/            \
    -lConanZero                \
    -lglut                     \

SOURCES +=                     \
    main.cc                    \
    ConanWindow.cc             \
    ConanScreen.cc             \

HEADERS +=                     \
    ConanWindow.hh             \
    ConanScreen.hh             \

FORMS +=                       \
    ConanWindow.ui             \
