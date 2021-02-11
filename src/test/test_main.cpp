#include <QtTest>
#include "testdbmanager.h"
#include "testlistofissues.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    TestDBManager testDbManager;
    TestMainWindow testMainWindow;

    return QTest::qExec(&testDbManager, argc, argv) |
            QTest::qExec(&testMainWindow, argc, argv);
}
