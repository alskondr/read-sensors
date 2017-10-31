PROJECT_VERSION = 1.1

QT += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = read-sensors

TEMPLATE = app

SOURCES += src/main.cpp \
    src/SensorsReader.cpp \
    src/Sensor.cpp \
    src/SensorsDecoder.cpp \
    src/MainWindow.cpp \
    src/ProjectDirModel.cpp \
    src/ProjectModel.cpp \
    src/Log.cpp \
    src/ProjectSettings.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    include/SensorsReader.h \
    include/Sensor.h \
    include/SensorsDecoder.h \
    include/MainWindow.h \
    include/ProjectDirModel.h \
    include/ProjectModel.h \
    include/Log.h \
    include/ProjectSettings.h

FORMS += \
    forms/MainWindow.ui
