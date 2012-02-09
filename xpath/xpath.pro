#-------------------------------------------------
#
# Project testxbn
#
#-------------------------------------------------

QT       -= gui core

TARGET = xpath
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp
INCLUDEPATH += ../
win32: {
    OBJECTS_DIR = obj/win32/
	DESTDIR = ../bin/
	LIBS += -L../lib/win32/
}
unix:  {
    OBJECTS_DIR = obj/unix/
	DESTDIR = ../bin/
	LIBS += -L../lib/unix/
}
mac:   {
    OBJECTS_DIR = obj/mac/
	DESTDIR = ../bin/
	LIBS += -L../lib/mac/
}

LIBS += -L../lib/ \
    -llibxbn

