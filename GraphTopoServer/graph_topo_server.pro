#-------------------------------------------------
#
# Project created by QtCreator 2018-03-19T23:24:40
#
#-------------------------------------------------

QT       -= gui
QT += xml core

TARGET = graph_topo_server
TEMPLATE = app

DEFINES += D5000
contains(DEFINES,D5000)
{
    QTDIR = $$system(printenv QTDIR)
    !include($$QTDIR/lib/qmake.conf){
             error(the file $$QTDIR/lib/qmake.conf is not exist!!)
    }

    LIBS += -L$$LIB_DIR      \
        -lodb_apiall_lib
}


INCLUDEPATH += ../include

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += CConfigurationInfo.cpp \
    CGraphManager.cpp \
    CModel.cpp \
    CModelContainer.cpp \
    CModelFileLoader.cpp \
    CModelLoaderFactory.cpp \
    CModelMapper.cpp \
    CModelRtLoader.cpp \
    CPropertyReader.cpp \
    CPropertyReaderImpl.cpp \
    CRtModelContainer.cpp \
    GraphTopoServer.cpp

HEADERS += CConfigurationInfo.h\
        CGraphManager.h \
    CModel.h \
    CModelContainer.h \
    CModelFileLoader.h \
    CModelLoaderFactory.h \
    CModelMapper.h \
    CModelRtLoader.h \
    CPropertyReader.h \
    CPropertyReaderImpl.h \
    CRtModelContainer.h \
    GetAllRecFromRealdb.h \
    IModelLoader.h

LIBS += -L../lib\
        -lGraphCore

unix {
    target.path = /usr/bin
    INSTALLS += target
}
