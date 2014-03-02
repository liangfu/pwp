
INCLUDEPATH += . 
WARNINGS += -Wall
unix:TEMPLATE = lib
win32:TEMPLATE = vclib
DEPENDPATH += . include src
QT=
DEFINES -= UNICODE

CONFIG += lib debug

UI_DIR = include
MOC_DIR = .moc
OBJECTS_DIR = .obj
DESTDIR = ../../lib

