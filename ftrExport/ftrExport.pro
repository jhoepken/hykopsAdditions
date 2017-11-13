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
        -lserializeemf \
        -lhykops_ducts

INCLUDEPATH +=  . \
                $$(HYKOPS_LIB_DIR) \
                $$(HYKOPS_PROJECT_DIR)/hykops_rudder \
                $$(HYKOPS_PROJECT_DIR)/hykops_core \
                $$(HYKOPS_PROJECT_DIR)/hykops_data \
                $$(HYKOPS_PROJECT_DIR)/serializeemf \
                ../ducts/genericDuct

DEPENDPATH +=  . \
                $$(HYKOPS_LIB_DIR) \
                $$(HYKOPS_PROJECT_DIR)/hykops_rudder \
                $$(HYKOPS_PROJECT_DIR)/hykops_core \
                $$(HYKOPS_PROJECT_DIR)/hykops_data \
                $$(HYKOPS_PROJECT_DIR)/serializeemf \
                ../ducts/genericDuct

SOURCES = ftrExport.cpp

# install
unix {
    target.path = .
    INSTALLS += target
}


message("--------------------------------------------------------------------------------")
message($$(HYKOPS_PROJECT_DIR))
message(">>>")
message($$(HYKOPS_LIB_DIR))
message(">>>")
message($$LIBS)
message("--------------------------------------------------------------------------------")
