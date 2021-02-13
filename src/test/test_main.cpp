#include <QtTest>
#include "testcontrollerdb.h"
#include "testcontrollerdialogs.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    TestControllerDB testDbManager;
    TestControllerDialogs testDialogManager;

    return QTest::qExec(&testDbManager, argc, argv) |
            QTest::qExec(&testDialogManager, argc, argv);
}
