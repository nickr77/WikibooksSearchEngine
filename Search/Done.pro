TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    avlnode.cpp \
    avltreeinterface.cpp \
    docindex.cpp \
    docparse.cpp \
    faststem.cpp \
    hashtableinterface.cpp \
    indexinterface.cpp \
    pageinfo.cpp \
    porter2_stemmer.cpp \
    queryprocessor.cpp \
    stopremover.cpp \
    stresstest.cpp \
    tagstack.cpp \
    worddata.cpp

HEADERS += \
    avlnode.h \
    avltreeinterface.h \
    docindex.h \
    docparse.h \
    faststem.h \
    hashtableinterface.h \
    indexinterface.h \
    pageinfo.h \
    porter2_stemmer.h \
    queryprocessor.h \
    stopremover.h \
    stresstest.h \
    tagstack.h \
    worddata.h

