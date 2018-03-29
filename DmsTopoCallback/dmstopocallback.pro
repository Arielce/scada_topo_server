!include(../make.conf){
         error(the file ../make.conf is not exist!!)
}

QT       -= gui

TARGET = dmsTopoCallback
TEMPLATE = lib

DEFINES += DMSTOPOCALLBACK_LIBRARY



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
        -lodb_apiall_lib
}

LIBS += -L../lib \
    -lGraphCore

INCLUDEPATH += ../interface \
                ../idls

HEADERS += \
    cdmstoposervice.h \
    cdmstopoimpl.h \
    ../interface/ITopoService.h \
    ../idls/DmsTopoData_m.h

SOURCES += \
    cdmstoposervice.cpp \
    cdmstopoimpl.cpp \
    ../idls/DmsTopoData_m.cpp

unix::QMAKE_POST_LINK += cp ./lib$$TARGET* ../lib;
unix {
    target.path = ../lib
    INSTALLS += target
}

