QT       += core gui
QT += serialport
QT += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    com_control.cpp \
    main.cpp \
    opencv_data.cpp \
    widget.cpp

HEADERS += \
    com_control.h \
    opencv_data.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -LE:\OpenCV4.11_mingw8.10\x64\mingw\lib \
        -lopencv_world4110

INCLUDEPATH += E:\OpenCV4.11_mingw8.10\include
DEPENDPATH += E:\OpenCV4.11_mingw8.10\include

