QT       -= gui

TARGET = ConanFile
TEMPLATE = lib

DEPENDPATH +=                  \
    ../ConanZero/              \

INCLUDEPATH +=                 \
    ../ConanZero/              \

LIBS +=                        \
    -L../ConanZero/            \
    -lConanZero                \

DEFINES += CONANFILE_LIBRARY

SOURCES +=                     \
    TextFile.cc                \

HEADERS +=                     \
    ConanFileGlobal.hh         \
    TextFile.hh                \
