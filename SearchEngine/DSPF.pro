TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        documentparser.cpp \
        filekey.cpp \
        main.cpp \
        porter2_stemmer.cpp \
        wordcorrector.cpp

HEADERS += \
    avltree.h \
    documentparser.h \
    filekey.h \
    hashtable.h \
    index.h \
    porter2_stemmer.h \
    wordcorrector.h
