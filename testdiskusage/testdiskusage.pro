QT += testlib
TEMPLATE = app
TARGET = testdiskusage 

INCLUDEPATH += . ../diskusage


# Input
SOURCES += testdiskusage.cpp ../diskusage/diskusage.h ../diskusage/diskusage.cpp  
