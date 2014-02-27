
INCLUDEPATH += . 
WARNINGS += -Wall
unix:TEMPLATE = lib
win32:TEMPLATE = vclib
DEPENDPATH += . include src
INCLUDEPATH += . src include ../cxcore/include ../cv/include
QT=
DEFINES -= UNICODE
CONFIG += staticlib

UI_DIR = include
MOC_DIR = .moc
OBJECTS_DIR = .obj
DESTDIR = ../../lib