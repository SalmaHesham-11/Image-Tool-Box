QT       += core gui
QT       -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = tool_box
CONFIG   -= app_bundle

TEMPLATE = app
INCLUDEPATH += C:\opencv\release\install\include
LIBS += C:\opencv\release\bin\libopencv_core430.dll
LIBS += C:\opencv\release\bin\libopencv_highgui430.dll
LIBS += C:\opencv\release\bin\libopencv_imgcodecs430.dll
LIBS += C:\opencv\release\bin\libopencv_imgproc430.dll
LIBS += C:\opencv\release\bin\libopencv_calib3d430.dll
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
