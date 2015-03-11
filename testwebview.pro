#-------------------------------------------------
#
# Project created by QtCreator 2015-01-22T11:23:29
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = webview
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    mywebpage.cpp \
    jsonencode.cpp

HEADERS  += mainwindow.h \
    mywebpage.h \
    jsonencode.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    js.qrc
