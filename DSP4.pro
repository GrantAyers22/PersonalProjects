TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        dsstring.cpp \
        flight.cpp \
        flightplanner.cpp \
        main.cpp \
        test.cpp

HEADERS += \
    adjnode.h \
    catch.hpp \
    dsstring.h \
    flight.h \
    flightplanner.h \
    node.h \
    stack.h
