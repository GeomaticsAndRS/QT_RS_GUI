#-------------------------------------------------
#
# Project created by QtCreator 2013-07-11T08:28:33
#
#-------------------------------------------------

QT       += core gui

TARGET = subsetimg
TEMPLATE = app


SOURCES += main.cpp\
    transvoidtoint.cpp \
    showimagebase2.cpp \
    showimagebase1.cpp \
    mymainwindow.cpp \
    subsetimage.cpp

HEADERS  +=transvoidtoint.h \
    showimagebase2.h \
    showimagebase1.h \
    mymainwindow.h \
    subsetimage.h

FORMS    +=    showimagebase2.ui \
    showimagebase1.ui \
    mymainwindow.ui \
    subsetimage.ui

OTHER_FILES +=
    #DisplayImage.pro#

INCLUDEPATH+=/usr/local/include

LIBS+=-L/usr/local/lib -lgdal

RESOURCES += \
    mymainwindow.qrc
