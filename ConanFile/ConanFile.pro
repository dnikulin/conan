QT       -= gui

TARGET = ConanFile
TEMPLATE = lib

DESTDIR = ../Release/

DEPENDPATH +=                  \
    ../ConanZero/              \

INCLUDEPATH +=                 \
    ../ConanZero/              \

LIBS +=                        \
    -L../Release/              \
    -lConanZero                \

DEFINES += CONANFILE_LIBRARY

SOURCES +=                     \
    TextFile.cc                \
    FileWorker.cc              \

HEADERS +=                     \
    ConanFileGlobal.hh         \
    TextFile.hh                \
    FileWorker.hh              \
