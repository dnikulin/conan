QT       -= gui

TARGET = ConanZero
TEMPLATE = lib

DESTDIR = ../Release/

DEFINES += CONANZERO_LIBRARY

SOURCES +=                     \
    Device.cc                  \
    SharedVolume.cc            \

HEADERS +=                     \
    ConanZeroGlobal.hh         \
    Device.hh                  \
    Math.hh                    \
    Volume.hh                  \
    SharedVolume.hh            \

LIBS +=                        \
    -lOpenCL                   \
