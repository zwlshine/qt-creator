INCLUDEPATH *= $$PWD $$PWD/..

DEFINES += QSCRIPTHIGHLIGHTER_BUILD_LIB

SOURCES += $$PWD/qscriptincrementalscanner.cpp
HEADERS += $$PWD/qscriptincrementalscanner.h $$PWD/qscripthighlighter_global.h

contains(QT, gui) {
    SOURCES += $$PWD/qscripthighlighter.cpp
    HEADERS += $$PWD/qscripthighlighter.h
}
