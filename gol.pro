TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -std=c11

SOURCES += main.c \
    gol.c \
    gol-private.c

HEADERS += \
    gol.h \
    gol-private.h

