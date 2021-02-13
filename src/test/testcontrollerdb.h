#include <QtTest/QtTest>

#include "controllerdb.h"


class TestControllerDB: public QObject
{
    Q_OBJECT

    public:
        QString testDbNanme = "test_db";

        ControllerDB* dbManager;
        ~TestControllerDB();

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
