#include "testdbmanager.h"
#include <QSqlQuery>


TestDBManager::~TestDBManager()
{
    delete dbManager;
}

void TestDBManager::initTestCase()
{
    this->dbManager = new DBManager("localhost", "admin", 3306, "test_connection");
    this->dbManager->createNewDB(this->testDbNanme);
    this->dbManager->connectToDb(this->testDbNanme);
}

void TestDBManager::testNewDBwasCreated()
{
    // Checks whether the test DB was created successfully

    std::vector<QString> databases = this->dbManager->getDatabases();
    QVERIFY(std::find(databases.begin(), databases.end(), this->testDbNanme) != databases.end());
}


void TestDBManager::testNewIssueCreation()
{
    // Checks whether a new issue in the DB can be created sucessfully

    QString expectedIssueID = "DUMMY1";
    QString expectedIssueTitle = "Dummy Test Issue";

    QString issueID;
    QString issueTitle;

    this->dbManager->createIssue(expectedIssueID.toStdString(), expectedIssueTitle.toStdString());

    QSqlQuery qry(this->dbManager->mDatabase);
    QString query = "SELECT * FROM overview";

    qry.prepare(query);

    if (qry.exec())
    {
        while (qry.next())
        {
            issueID = qry.value(1).toString();
            issueTitle = qry.value(2).toString();
        }
    }

    QVERIFY(issueID == expectedIssueID);
    QVERIFY(issueTitle == expectedIssueTitle);
}

void TestDBManager::testChangeIssueTitle()
{
    QString expectedIssueID = "DUMMY1";
    QString expectedIssueTitle = "Modified Test Issue";

    QString issueID;
    QString issueTitle;

    this->dbManager->updateIssueTitle(expectedIssueID.toStdString(), expectedIssueTitle.toStdString());

    QSqlQuery qry(this->dbManager->mDatabase);
    QString query = "SELECT * FROM overview";

    qry.prepare(query);

    if (qry.exec())
    {
        while (qry.next())
        {
            issueID = qry.value(1).toString();
            issueTitle = qry.value(2).toString();
        }
    }

    QVERIFY(issueID == expectedIssueID);
    QVERIFY(issueTitle == expectedIssueTitle);
}

void TestDBManager::testChangeIssueDescription()
{
    QString expectedIssueID = "DUMMY1";
    QString expectedIssueDescription = "This is some random description to update in the DB";

    QString issueID;
    QString issueDescription;

    this->dbManager->updateIssueDescription(expectedIssueID.toStdString(), expectedIssueDescription.toStdString());

    QSqlQuery qry(this->dbManager->mDatabase);
    QString query = "SELECT * FROM contents";

    qry.prepare(query);

    if (qry.exec())
    {
        while (qry.next())
        {
            issueID = qry.value(1).toString();
            issueDescription = qry.value(2).toString();
        }
    }

    QVERIFY(issueID == expectedIssueID);
    QVERIFY(issueDescription == expectedIssueDescription);
}

void TestDBManager::testRemoveIssue()
{
    QString expectedIssueID = "DUMMY1";

    QString issueID;

    QSqlQuery qry(this->dbManager->mDatabase);
    QString query = "SELECT * FROM contents";


    qry.prepare(query);

    if (qry.exec())
    {
        while (qry.next())
        {
            issueID = qry.value(1).toString();
        }
    }
    QVERIFY(issueID == expectedIssueID);

    this->dbManager->removeIssue(expectedIssueID.toStdString());

    qry.prepare(query);
    qry.exec();

    QVERIFY(! qry.next());
}


void TestDBManager::cleanupTestCase()
{
    // this->dbManager->deleteDB(this->testDbNanme);
    this->dbManager->closeConnection();
}
