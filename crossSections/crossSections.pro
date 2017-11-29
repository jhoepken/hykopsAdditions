TEMPLATE = lib

QT += core \
    xml

CONFIG *= c++11

TARGET = hykops_crossSections

LIBS_PATH = -L$$(HYKOPS_LIB_DIR)

LIBS += -L$$(HYKOPS_LIB_DIR) \
        -lhykops_data \
        -lhykops_core \
        -lserializeemf

INCLUDEPATH +=  . \
                $$(HYKOPS_LIB_DIR) \
                $$(HYKOPS_PROJECT_DIR)/hykops_core \
                $$(HYKOPS_PROJECT_DIR)/hykops_data \
                $$(HYKOPS_PROJECT_DIR)/serializeemf

DEPENDPATH +=  . \
                $$(HYKOPS_LIB_DIR) \
                $$(HYKOPS_PROJECT_DIR)/hykops_core \
                $$(HYKOPS_PROJECT_DIR)/hykops_data \
                $$(HYKOPS_PROJECT_DIR)/serializeemf

SOURCES += genericCrossSection/genericCrossSection.cpp \
            pointListCrossSection/pointListCrossSection.cpp 

HEADERS += genericCrossSection/genericCrossSection.h\
            pointListCrossSection/pointListCrossSection.h

# install
unix {
    target.path = .
    INSTALLS += target
    DESTDIR = $$(HYKOPS_LIB_DIR)
}
