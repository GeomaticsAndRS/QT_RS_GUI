#-------------------------------------------------
#
# Project created by QtCreator 2013-07-15T14:06:43
#
#-------------------------------------------------

QT       += core gui

TARGET = IDentifyTool
TEMPLATE = app


SOURCES += main.cpp\
    transvoidtoint.cpp \
    showimagebase2.cpp \
    showimagebase1.cpp \
    geometrycorrection.cpp \
    identifyimage.cpp \
    transvoidtointone.cpp \
    pastearea.cpp

HEADERS  += \
    transvoidtoint.h \
    showimagebase2.h \
    showimagebase1.h \
    geometrycorrection.h \
    identifyimage.h \
    transvoidtointone.h \
    pastearea.h

FORMS    += \
    showimagebase2.ui \
    showimagebase1.ui \
    geometrycorrection.ui \
    identifyimage.ui \
    pastearea.ui

OTHER_FILES += \
    IDentifyTool.pro.user

RESOURCES += \
    geometrycorrection.qrc

INCLUDEPATH+=/usr/local/include

LIBS+=-L/usr/local/lib -lgdal
