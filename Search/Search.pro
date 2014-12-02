TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    docparse.cpp \
    stopremover.cpp \
    indexinterface.cpp \
    avltreeinterface.cpp \
    hashtableinterface.cpp \
    porter2_stemmer.cpp \
    avlnode.cpp \
    faststem.cpp \
    worddata.cpp \
    pageinfo.cpp \
    docindex.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    docparse.h \
    stopremover.h \
    indexinterface.h \
    avltreeinterface.h \
    hashtableinterface.h \
    porter2_stemmer.h \
    avlnode.h \
    faststem.h \
    worddata.h \
    pageinfo.h \
    docindex.h

