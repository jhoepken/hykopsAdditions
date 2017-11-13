TEMPLATE = lib

QT += core \
    xml

CONFIG *= c++11

TARGET = hykops_ducts

LIBS_PATH = -L$$(HYKOPS_LIB_DIR)

LIBS += -L$$(HYKOPS_LIB_DIR) \
        -lhykops_data \
        -lhykops_core \
        -lhykops_rudder \
        -lserializeemf

INCLUDEPATH +=  . \
                $$(HYKOPS_LIB_DIR) \
                $$(HYKOPS_PROJECT_DIR)/hykops_rudder \
                $$(HYKOPS_PROJECT_DIR)/hykops_core \
                $$(HYKOPS_PROJECT_DIR)/hykops_data \
                $$(HYKOPS_PROJECT_DIR)/serializeemf

DEPENDPATH +=  . \
                $$(HYKOPS_LIB_DIR) \
                $$(HYKOPS_PROJECT_DIR)/hykops_rudder \
                $$(HYKOPS_PROJECT_DIR)/hykops_core \
                $$(HYKOPS_PROJECT_DIR)/hykops_data \
                $$(HYKOPS_PROJECT_DIR)/serializeemf

SOURCES += genericDuct/genericDuct.cpp

HEADERS += genericDuct/genericDuct.h

# install
unix {
    target.path = .
    INSTALLS += target
    DESTDIR = $$(HYKOPS_LIB_DIR)
}
