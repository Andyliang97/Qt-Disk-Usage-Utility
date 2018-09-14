CPPLIBS=$$(CPPLIBS)
isEmpty( CPPLIBS ){
    error("You need to difine CPPLIBS environment variable.")
}

DESTDIR = $$(CPPLIBS)
LIBS += -L$$(CPPLIBS)
TEMPLATE=lib


QT += xml
QT += widgets

HEADERS += argulist.h
SOURCES += argulist.cpp

