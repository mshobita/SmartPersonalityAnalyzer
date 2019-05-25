TEMPLATE = app
TARGET = PlatformClient

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += network widgets
requires(qtConfig(combobox))

SOURCES += \
    main.cpp \
    platformclientgui.cpp \
    platformclient.cpp \
    book.cpp \
    tag.cpp \
    movie.cpp \
    quote.cpp

HEADERS += \
    platformclientgui.h \
    platformclient.h \
    book.h \
    tag.h \
    movie.h \
    quote.h

