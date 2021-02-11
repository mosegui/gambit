#include "viewmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ViewMainWindow w;
    w.setWindowTitle("GAMBIT");

    w.show();
    return a.exec();
}
