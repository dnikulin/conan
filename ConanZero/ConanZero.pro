QT       -= gui

TARGET = ConanZero
TEMPLATE = lib

DEFINES += CONANZERO_LIBRARY

SOURCES +=                     \
    Device.cc                  \

HEADERS +=                     \
    ConanZeroGlobal.hh         \
    Device.hh                  \
    Math.hh                    \
    Volume.hh                  \

LIBS +=                        \
    -lOpenCL                   \
