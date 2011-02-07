QT       -= gui

TARGET = ConanZero
TEMPLATE = lib

DEFINES += CONANZERO_LIBRARY

SOURCES +=                     \
    Device.cc                  \

HEADERS +=                     \
    ConanZeroGlobal.hh         \
    ConanTypes.hh              \
    Device.hh                  \
    Math.hh                    \

LIBS +=                        \
    -lOpenCL                   \
