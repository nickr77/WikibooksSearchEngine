TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    docparse.cpp \
    stopremover.cpp \
    indexinterface.cpp \
    avltreeinterface.cpp \
    hashtableinterface.cpp \
    porter2_stemmer.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    docparse.h \
    stopremover.h \
    indexinterface.h \
    avltreeinterface.h \
    hashtableinterface.h \
    porter2_stemmer.h

