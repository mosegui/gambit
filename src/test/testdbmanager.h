#include <QtTest/QtTest>

#include "dbmanager.h"


class TestDBManager: public QObject
{
    Q_OBJECT

public:
    QString testDbNanme = "test_db";

    DBManager* dbManager;
    ~TestDBManager();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testNewDBwasCreated();
    void testNewIssueCreation();
    void testChangeIssueTitle();
    void testChangeIssueDescription();
    void testRemoveIssue();
};
