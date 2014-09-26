#-------------------------------------------------
#
# Project created by QtCreator 2014-05-22T09:19:17
#
#-------------------------------------------------

TARGET_NAME = ztoolkit
DEFINES_NAME = MPLIB_LIBRARY
###############################################################################

#DEFINES += $${DEFINES_NAME}

###############################################################################
#contains(DEFINES, $${DEFINES_NAME}) {
#message(TTTTTTTTTTTTTTTTTT)
#message(liblibliblibliblib)
#TEMPLATE = lib
#DESTDIR  = ../../../lib
#}
###############################################################################
!contains(DEFINES, $${DEFINES_NAME}) {
message(TTTTTTTTTTTTTTTTTT)
message(appappappappappapp)
TEMPLATE = app
SOURCES += src/main.cpp
DESTDIR  = ../../../bin
win32: RC_FILE = ztoolkit.rc
}
###############################################################################
TARGET = $${TARGET_NAME}
###############################################################################
QT       += network
###############################################################################
win32 {
CONFIG(debug, debug|release): OBJECTS_DIR = ../../../TEMP/$${TARGET}/debug
CONFIG(release, debug|release): OBJECTS_DIR = ../../../TEMP/$${TARGET}/release
CONFIG(debug, debug|release) : TARGET = $${TARGET_NAME}d
} else {
OBJECTS_DIR = ../../../TEMP/$${TARGET}
}
###############################################################################
UI_DIR      = $${OBJECTS_DIR}/uic
MOC_DIR     = $${OBJECTS_DIR}/moc
RCC_DIR     = $${OBJECTS_DIR}/rcc
INCLUDEPATH += $${OBJECTS_DIR}/uic
###############################################################################
#INCLUDEPATH += ./copyfile
INCLUDEPATH += ./include
INCLUDEPATH += ../../src_lib/mplib/include
###############################################################################
LIBS += -L../../../lib -lmplib
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################

HEADERS += \
    include/mainwindow.h \
    include/zfiletool.h \
    include/zdeletefiledlg.h \
    include/zrenamefiledlg.h \
    include/zcopyfiledlg.h \
    include/zshutdowndlg.h \
    include/zposcolordlg.h

SOURCES += \
     src/mainwindow.cpp \
     src/zfiletool.cpp \
     src/zdeletefiledlg.cpp \
     src/zrenamefiledlg.cpp \
     src/zcopyfiledlg.cpp \
     src/zshutdowndlg.cpp \
     src/zposcolordlg.cpp

FORMS += \
    ui/mainwindow.ui \
    ui/zdeletefiledlg.ui \
    ui/zrenamefiledlg.ui \
    ui/zcopyfiledlg.ui \
    ui/zshutdowndlg.ui \
    ui/zposcolordlg.ui

RESOURCES += \
    source.qrc
