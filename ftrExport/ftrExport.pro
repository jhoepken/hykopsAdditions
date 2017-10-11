TEMPLATE = app

QT += core \
    xml

CONFIG *= c++11

TARGET = ftrExport

LIBS_PATH = -L$$(HYKOPS_LIB_DIR)

LIBS += -L$$(HYKOPS_LIB_DIR) \
        -lhykops_data \
        -lhykops_core \
        -lhykops_rudder \
        -lserializeemf

INCLUDEPATH +=  . \
                $$(BOOST_INCLUDE) \
                $$(HYKOPS_LIB_DIR) \
                $$(HYKOPS_PROJECT_DIR)/hykops_rudder \
                $$(HYKOPS_PROJECT_DIR)/hykops_core \
                $$(HYKOPS_PROJECT_DIR)/hykops_data \
                $$(HYKOPS_PROJECT_DIR)/serializeemf

DEPENDPATH +=  . \
                $$(BOOST_LIB) \
                $$(HYKOPS_LIB_DIR) \
                $$(HYKOPS_PROJECT_DIR)/hykops_rudder \
                $$(HYKOPS_PROJECT_DIR)/hykops_core \
                $$(HYKOPS_PROJECT_DIR)/hykops_data \
                $$(HYKOPS_PROJECT_DIR)/serializeemf

SOURCES = ftrExport.cpp

# install
unix {
    target.path = .
    INSTALLS += target
}
macx {
    QMAKE_CC = clang
    QMAKE_CXX = clang++

    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_CCFLAGS += -std=c++11

    DESTDIR = $$(HYKOPS_LIB_DIR)
    target.path = $$(HYKOPS_LIB_DIR)
    INSTALLS += target
}


message("--------------------------------------------------------------------------------")
message($$(HYKOPS_PROJECT_DIR))
message(">>>")
message($$(HYKOPS_LIB_DIR))
message(">>>")
message($$LIBS)
message("--------------------------------------------------------------------------------")
