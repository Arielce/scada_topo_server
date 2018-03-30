QT += core xml
QT -= gui

CONFIG += c++11

TARGET = test_func
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../GraphTopoServer \
        ../include

DEFINES += D5000
contains(DEFINES,D5000)
{
    unix{
            QTDIR = $$system(printenv QTDIR)
            CURRENT_PROJECT_PATH = $$system(pwd)
    }
    QTDIR = $$system(printenv QTDIR)
    !include($$QTDIR/lib/qmake.conf){
             error(the file $$QTDIR/lib/qmake.conf is not exist!!)
    }

    LIBS += -L$$LIB_DIR      \
        -lodb_apiall_lib \
        -lparamanage
}

LIBS += -L../lib\
        -lGraphCore

SOURCES += main.cpp \
    ../GraphTopoServer/CPropertyReader.cpp \
    ../GraphTopoServer/CPropertyReaderImpl.cpp \
    ../GraphTopoServer/CModel.cpp \
    ../GraphTopoServer/CConfigurationInfo.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    ../GraphTopoServer/CPropertyReader.h \
    ../GraphTopoServer/CPropertyReaderImpl.h \
    ../GraphTopoServer/CModel.h \
    ../GraphTopoServer/CConfigurationInfo.h
