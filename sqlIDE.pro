#-------------------------------------------------
#
# Project created by QtCreator 2017-09-15T09:11:38
#
#-------------------------------------------------

QT       += core gui  sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sqlIDE
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    setdialog.cpp \
    getparameter.cpp

HEADERS  += mainwindow.h \
    setdialog.h \
    getparameter.h

FORMS    += mainwindow.ui \
    setdialog.ui

#LIBS += qsqlocid.lib \qsqloci.lib
#LIBS += -lqsqloci
#LIBS += E:\plugins\sqldrivers\qsqloci.lib
LIBS += $$PWD/qsqloci.lib
LIBS += $$PWD/qsqlocid.lib
#CONFIG += debug_and_release
#CONFIG(debug,debug|release) {
# unix|win32: LIBS += -lQtCored
# unix|win32: LIBS += -lQtGuid
# unix|win32: LIBS += -lQtNetworkd
#unix|win32: LIBS += -lqsqlocid
#} else {
# unix|win32: LIBS += -lQtCore
# unix|win32: LIBS += -lQtGui
# unix|win32: LIBS += -lqsqloci
#}
