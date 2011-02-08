QT       += core gui

TARGET = ConanMock
TEMPLATE = lib
CONFIG += plugin

DESTDIR = ../Plugins/

DEPENDPATH +=                  \
    ../ConanZero/              \
    ../ConanLive/              \

INCLUDEPATH +=                 \
    ../ConanZero/              \
    ../ConanLive/              \

LIBS +=                        \
    -L../ConanZero/            \
    -lConanZero                \

SOURCES +=                     \
    ConanMock.cc               \
    MockDialog.cc              \

HEADERS +=                     \
    ConanMock.hh               \
    MockDialog.hh              \

FORMS +=                       \
    MockDialog.ui              \
