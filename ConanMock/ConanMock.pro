QT       += core gui

TARGET = ConanMock
TEMPLATE = lib
CONFIG += plugin

DESTDIR = ../Release/Plugins/

DEPENDPATH +=                  \
    ../ConanZero/              \
    ../ConanFile/              \
    ../ConanLive/              \

INCLUDEPATH +=                 \
    ../ConanZero/              \
    ../ConanFile/              \
    ../ConanLive/              \

LIBS +=                        \
    -L../Release/              \
    -lConanZero                \

SOURCES +=                     \
    ConanMock.cc               \
    MockDialog.cc              \

HEADERS +=                     \
    ConanMock.hh               \
    MockDialog.hh              \

FORMS +=                       \
    MockDialog.ui              \
