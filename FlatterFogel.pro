#-------------------------------------------------
#
# Project created by QtCreator 2017-09-20T17:22:55
#
#-------------------------------------------------

QT       += core gui network multimedia purchasing
android: QT += androidextras
android: include(D:/FF_QT515/android_openssl-master/openssl.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlatterFogel
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        frmmain.cpp \
    networkmanager.cpp \
    player.cpp \
    obstacle.cpp \
    blus.cpp \
    scoreboardplayer.cpp \
    shop.cpp \
    pxan.cpp \
    window.cpp \
    star.cpp \
    text.cpp \
    translation.cpp \
    scoreboard.cpp \
    background.cpp \
    settings.cpp \
    enemy.cpp \
    projectile.cpp

HEADERS += \
        frmmain.h \
    networkmanager.h \
    player.h \
    obstacle.h \
    blus.h \
    scoreboardplayer.h \
    shop.h \
    pxan.h \
    window.h \
    star.h \
    text.h \
    translation.h \
    scoreboard.h \
    background.h \
    settings.h \
    enemy.h \
    projectile.h

FORMS += \
        frmmain.ui

CONFIG += mobility c++14
MOBILITY = 

QMAKE_CXXFLAGS += -fexceptions -frtti

RESOURCES += \
    resources.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    images/buttons/buttonSettings.png

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
ANDROID_ABIS += arm64-v8a armeabi-v7a

#include(D:/FF_QT515/purchasing/purchasing.pri);


