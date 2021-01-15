#include "testdbmanager.h"
#include <QSqlQuery>

/*    - Change issue title and check it changes successfully
 *    - Change issue description and check it changes successfully
 *    - remove issue and check it is not there any more
 */


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


void TestDBManager::cleanupTestCase()
{
    this->dbManager->deleteDB(this->testDbNanme);
    this->dbManager->closeConnection();
}
