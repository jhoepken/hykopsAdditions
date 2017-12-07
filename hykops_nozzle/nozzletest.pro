QT += core xml\
    testlib \
    xml

CONFIG += c++11

TARGET = nozzletest

LIBS_PATH = -L/tmp/libs
INC_PATH = -I../hykops_data \
            -I../hykops_core \
            -I../hykops_nozzle \
            -I../serializeemf

LIBS += -L/tmp/libs/ \
        -L/tmp/libs/hykops_data \
        -L../hykops_data \
        -L../hykops_core \
        -L../hykops_nozzle \
        -L../serializeemf \
        -lhykops_data \
        -lhykops_core \
        -lhykops_propeller \
        -lserializeemf

DEPENDPATH += . \
                /tmp/libs \
                ../hykops_nozzle \
                ../hykops_core \
                ../hykops_data \
                ../serializeemf

INCLUDEPATH += . \
                /tmp/libs \
                ../hykops_nozzle \
                ../hykops_core \
                ../hykops_data \
                ../serializeemf

SOURCES = NozzleFactory.cpp

# install
unix {
    target.path = .
    INSTALLS += target
}
