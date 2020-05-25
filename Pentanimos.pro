QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = bin

SOURCES += \
    src/game.cpp \
    src/gamestatus.cpp \
    src/grid.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/pentamino.cpp \
    src/scene.cpp \
    src/settings.cpp

HEADERS += \
    src/game.h \
    src/gamestatus.h \
    src/grid.h \
    src/mainwindow.h \
    src/pentamino.h \
    src/scene.h \
    src/settings.h

FORMS += \
    src/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /usr/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    CHANGELOG \
    COPYING \
    INSTALL.md \
    README.md \
    doc/MainWindow.png
