#-------------------------------------------------
#
# Project created by QtCreator 2017-02-14T10:00:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CustomWindow
TEMPLATE = app


SOURCES += main.cpp\
         CustomWindow.cpp \
        WindowTitle.cpp 



HEADERS  += \
           CustomWindow.h \
        WindowTitle.h  


FORMS += \
    CustomWindow.ui


RESOURCES += \
	CustomWindow.qrc

MOC_DIR = temp/moc
RCC_DIR = temp/rcc
UI_DIR = temp/ui
OBJECTS_DIR = temp/obj
DESTDIR = bin
