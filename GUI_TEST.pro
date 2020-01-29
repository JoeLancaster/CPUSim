#-------------------------------------------------
#
# Project created by QtCreator 2014-03-10T18:18:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI_TEST
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp\
        cpu.cpp\
        cpu_ex.cpp\
        mutable_cpu.cpp\
        regpair.cpp \
    highlighter.cpp \
    assembler_strings.cpp \
    view.cpp \
    memory_numbers.cpp

HEADERS  += mainwindow.h\
        assembler.h\
        assembler_exception.h\
        cpu.h\
        cpu_ex.h\
        mutable_cpu.h\
        psw.h\
        regpair.h \
    highlighter.h \
    ops.h \
    opcode.h \
    regs.h \
    build_constants.h \
    assembler_strings.h \
    runtime_exception.h \
    cpu_exception.h \
    memory_violation_exception.h \
    stack_exception.h \
    stack_overflow_exception.h \
    quick_message_box.h \
    view.h \
    memory_numbers.h \
    opcode_not_found_exception.h \
    register_not_found_exception.h \
    stack_underflow_exception.h

FORMS    += mainwindow.ui
