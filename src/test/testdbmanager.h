#include <QtTest/QtTest>

#include "controllerdb.h"


class TestDBManager: public QObject
{
    Q_OBJECT

public:
    QString testDbNanme = "test_db";

    ControllerDB* dbManager;
    ~TestDBManager();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testNewDBwasCreated();
    void testNewIssueCreation();
    void testChangeIssueTitle();
    void testChangeIssueDescription();
    void testRemoveIssue();

private:
    std::vector<QString> runSingleRecordQuery(QString);

};
