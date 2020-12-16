#include "listofissues.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListOfIssues w;

    w.show();
    return a.exec();
}
