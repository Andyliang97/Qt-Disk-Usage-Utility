CPPLIBS=$$(CPPLIBS)
isEmpty( CPPLIBS ){
    error("You need to difine CPPLIBS environment variable.")
}

INCLUDEPATH = $$(CPPLIBS)/argulist
LIBS += -largulist -L$$(CPPLIBS)

QT -= gui


CONFIG += c++11 console
CONFIG -= app_bundle

TEMPLATE = app
TARGET = diskusage

# Input
SOURCES += diskusage.h diskusage.cpp main.cpp
