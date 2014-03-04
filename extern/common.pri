
INCLUDEPATH += . 
WARNINGS += -Wall
unix:TEMPLATE = lib
win32:TEMPLATE = vclib
DEPENDPATH += . include src
QT=
DEFINES -= UNICODE

CONFIG += lib debug
win32:TARGET = $$join(TARGET,,lib,) 

#build_pass:CONFIG(debug, debug|release) {
#  TARGET = $$join(TARGET,,,_debug) 
#}

UI_DIR = include
MOC_DIR = .moc
OBJECTS_DIR = .obj
DESTDIR = ../../lib

