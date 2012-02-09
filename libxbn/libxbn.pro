# -------------------------------------------------
# Project libxbn
# -------------------------------------------------
QT -= core \
    gui
TARGET = libxbn
TEMPLATE = lib
CONFIG += staticlib
SOURCES += xbnode.cpp \
    xbdata.cpp \
    xbstring.cpp \
    xbnparser.cpp \
    xbn_xpath.cpp \
    xbn_xslt.cpp \
    xbnnode_plugins.cpp \
    xbn_stack.cpp \
    xbn_state.cpp \
    xbn_document.cpp \
    xbn_helper.cpp \
    sptr.cpp \
    xslt_plugins/xbn_xslt_plugins.cpp \
    xpath_plugins/xbn_xpath_plugins.cpp \
    xpath_plugins/xpath_select.cpp \
    xpath_plugins/xpath_pipe.cpp \
    xpath_plugins/xpath_condition.cpp \
    xpath_plugins/xpath_logical.cpp \
    xpath_plugins/xpath_comparsion.cpp \
    xpath_plugins/xpath_math.cpp \
    xpath_plugins/1_0/xpath_boolean.cpp \
    xpath_plugins/1_0/xpath_ceiling.cpp \
    xpath_plugins/1_0/xpath_floor.cpp \
    xpath_plugins/1_0/xpath_round.cpp \
    xpath_plugins/1_0/xpath_concat.cpp \
    xpath_plugins/1_0/xpath_contains.cpp \
    xpath_plugins/1_0/xpath_count.cpp \
    xpath_plugins/1_0/xpath_current.cpp \
    xpath_plugins/1_0/xpath_document.cpp \
    xpath_plugins/1_0/xpath_number.cpp \
    xpath_plugins/1_0/xpath_string.cpp \
    xpath_plugins/1_0/xpath_name.cpp \
    xpath_plugins/1_0/xpath_translate.cpp \
    xpath_plugins/1_0/xpath_id.cpp \
    xpath_plugins/1_0/xpath_available.cpp \
    xpath_plugins/1_0/xpath_text.cpp \
    xpath_plugins/1_0/xpath_position.cpp \
    xpath_plugins/1_0/xpath_sum.cpp \
    xslt_plugins/1_0/xslt_template.cpp \
    xslt_plugins/1_0/xslt_apply_templates.cpp \
    xslt_plugins/1_0/xslt_choose.cpp \
    xslt_plugins/1_0/xslt_value_of.cpp \
    xslt_plugins/1_0/xslt_attribute.cpp \
    xslt_plugins/1_0/xslt_element.cpp \
    xslt_plugins/1_0/xslt_copy.cpp \
    xslt_plugins/1_0/xslt_include.cpp \
    xslt_plugins/1_0/xslt_stylesheet.cpp \
    xslt_plugins/1_0/xslt_for_each.cpp \
    xslt_plugins/1_0/xslt_if.cpp \
    xslt_plugins/1_0/xslt_call_template.cpp \
    xslt_plugins/1_0/xslt_number.cpp \
    xslt_plugins/1_0/xslt_output.cpp \
    xslt_plugins/1_0/xslt_space.cpp \
    xslt_plugins/1_0/xslt_variable.cpp \
    xslt_plugins/1_0/xslt_param.cpp \
    xslt_plugins/1_0/xslt_sort.cpp \
    xslt_plugins/1_0/xslt_namespace_alias.cpp \
    xslt_plugins/1_0/xslt_message.cpp \
    xslt_plugins/1_0/xslt_key.cpp \
    xslt_plugins/1_0/xslt_fallback.cpp
HEADERS += xbn.h \
    xbnode.h \
    xbdata.h \
    xbstring.h \
    xbnparser.h \
    xbn_xpath.h \
    xbn_xslt.h \
    xbnnode_plugins.h \
    save_delete.h \
    xbn_stack.h \
    xbn_state.h \
    xbn_document.h \
    xbn_helper.h \
    sptr.h \
    xpath_plugins/xbn_xpath_plugins.h \
    xpath_plugins/xbn_xpath_plugins_1_0.h \
    xslt_plugins/xbn_xslt_plugins.h \
    xslt_plugins/xbn_xslt_plugins_1_0.h
INCLUDEPATH += ../ ./
win32: { 
    OBJECTS_DIR = obj/win32/
    DESTDIR = ../lib/win32/
    LIBS += -L../lib/win32/
}
unix: { 
    OBJECTS_DIR = obj/unix/
    DESTDIR = ../lib/unix/
    LIBS += -L../lib/unix/
}
mac: { 
    OBJECTS_DIR = obj/mac/
    DESTDIR = ../lib/mac/
    LIBS += -L../lib/mac/
}
