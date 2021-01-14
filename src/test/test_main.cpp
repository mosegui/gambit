#include <QtTest>
#include "testdbmanager.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    TestDBManager testDbManager;

    return QTest::qExec(&testDbManager, argc, argv);
}
