#pragma once

#include <QtTest/QtTest>

#include "viewmainwindow.h"
#include "controllerdialogs.h"


class TestControllerDialogs: public QObject
{
    Q_OBJECT

    public:
         ~TestControllerDialogs();

        ViewMainWindow* mainwindow;
        ControllerDialogs* dialogsManager;

    private slots:
        void initTestCase();

        void testOpenNewIssue();
        void testOpenNewSession();
};

