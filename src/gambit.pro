QT       += core gui sql

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

SOURCES += \
    controllerdb.cpp \
    controllerdialogs.cpp \
    main.cpp \
    viewexistingsessions.cpp \
    viewmainwindow.cpp \
    viewnewissue.cpp \
    viewnewsession.cpp

HEADERS += \
    controllerdb.h \
    controllerdialogs.h \
    viewexistingsessions.h \
    viewmainwindow.h \
    viewnewissue.h \
    viewnewsession.h

FORMS += \
    existingsessions.ui \
    mainwindow.ui \
    newissue.ui \
    newsession.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

test {
    message(Test build)

    QT += testlib
    TARGET = qttest-example-test
    SOURCES -= main.cpp

    HEADERS += \
        test/testcontrollerdb.h \
        test/testcontrollerdialogs.h

    SOURCES += \
        test/test_main.cpp \
        test/testcontrollerdb.cpp \
        test/testcontrollerdialogs.cpp

} else {
    message(Normal build)
}
