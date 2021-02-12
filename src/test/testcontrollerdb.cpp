#include "testcontrollerdb.h"
#include <QSqlQuery>


TestControllerDB::~TestControllerDB()
{
    delete dbManager;
}

void TestControllerDB::initTestCase()
{
    this->dbManager = new ControllerDB("localhost", "admin", 3306, "test_connection");
    this->dbManager->createNewDB(this->testDbNanme);
    this->dbManager->connectToDb(this->testDbNanme);
}

std::vector<QString> TestControllerDB::runSingleRecordQuery(QString query)
{
    // Use of this querying function is only indicated for queries known to return a single record

    QSqlQuery qry(this->dbManager->mDatabase);
    std::vector<QString> record_members;

    qry.prepare(query);

    if (qry.exec())
    {
        while (qry.next())
        {
            record_members.push_back(qry.value(1).toString());
            record_members.push_back(qry.value(2).toString());
        }
    }
    return record_members;
}


void TestControllerDB::testNewDBwasCreated()
{
    // Checks whether the test DB was created successfully

    std::vector<QString> databases = this->dbManager->getDatabases();
    QVERIFY(std::find(databases.begin(), databases.end(), this->testDbNanme) != databases.end());
}


void TestControllerDB::testNewIssueCreation()
{
    // Checks whether a new issue in the DB can be created sucessfully

    QString expectedIssueID = "DUMMY1";
    QString expectedIssueTitle = "Dummy Test Issue";
    QString query = "SELECT * FROM overview";

    this->dbManager->createIssue(expectedIssueID.toStdString(), expectedIssueTitle.toStdString());

    std::vector<QString> query_record_members = TestControllerDB::runSingleRecordQuery(query);

    QVERIFY(query_record_members[0] == expectedIssueID);
    QVERIFY(query_record_members[1] == expectedIssueTitle);
}

void TestControllerDB::testChangeIssueTitle()
{
    QString expectedIssueID = "DUMMY1";
    QString expectedIssueTitle = "Modified Test Issue";
    QString query = "SELECT * FROM overview";

    this->dbManager->updateIssueTitle(expectedIssueID.toStdString(), expectedIssueTitle.toStdString());

    std::vector<QString> query_record_members = TestControllerDB::runSingleRecordQuery(query);

    QVERIFY(query_record_members[0] == expectedIssueID);
    QVERIFY(query_record_members[1] == expectedIssueTitle);
}

void TestControllerDB::testChangeIssueDescription()
{
    QString expectedIssueID = "DUMMY1";
    QString expectedIssueDescription = "This is some random description to update in the DB";
    QString query = "SELECT * FROM contents";

    this->dbManager->updateIssueDescription(expectedIssueID.toStdString(), expectedIssueDescription.toStdString());

    std::vector<QString> query_record_members = TestControllerDB::runSingleRecordQuery(query);

    QVERIFY(query_record_members[0] == expectedIssueID);
    QVERIFY(query_record_members[1] == expectedIssueDescription);
}

void TestControllerDB::testRemoveIssue()
{
    QString expectedIssueID = "DUMMY1";
    QString query = "SELECT * FROM contents";

    std::vector<QString> query_record_members = TestControllerDB::runSingleRecordQuery(query);

    // Check the record os there before deleting it
    QVERIFY(query_record_members[0] == expectedIssueID);

    this->dbManager->removeIssue(expectedIssueID.toStdString());

    // Check for empty array, meaning the query returned no records (successfully deleted)
    QVERIFY(! TestControllerDB::runSingleRecordQuery(query).size());
}


void TestControllerDB::cleanupTestCase()
{
    this->dbManager->deleteDB(this->testDbNanme);
    this->dbManager->closeConnection();
}
