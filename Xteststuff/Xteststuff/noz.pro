#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T11:57:51
#
#-------------------------------------------------

TARGET = hykops_noztest
TEMPLATE = lib

CONFIG += c++11

DEFINES += LIBHYKOPS_NOZZLE_LIBRARY

unix:DESTDIR = /tmp/libs/
win32:DESTDIR = C:\tmp\libs\

SOURCES += \
    noztest.cpp \
    SIS.cpp \

HEADERS += \
    noztest.h \
    SIS.h 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH +=   ../hykops_core/\
                                ../serializeemf \
                                ../hykops_data/

LIBS += "-L/tmp/libs/" -lhykops_core -lhykops_data -lserializeemf
