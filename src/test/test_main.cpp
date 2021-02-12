#include <QtTest>
#include "testcontrollerdb.h"
//#include "testlistofissues.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    TestControllerDB testDbManager;
//    TestMainWindow testMainWindow;

    return QTest::qExec(&testDbManager, argc, argv); //|
//            QTest::qExec(&testMainWindow, argc, argv);
}
