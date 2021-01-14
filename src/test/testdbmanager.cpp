#include "testdbmanager.h"


/*    - CreateIssue in table and manually check it is there
 *    - Get issue ID and check it is correct
 *    - Get issue title and check it is correct
 *    - Get issue description and check it is correct
 *    - Change issue title and check it changes successfully
 *    - Change issue description and check it changes successfully
 *    - remove issue and check it is not there any more
 */


TestDBManager::~TestDBManager()
{
    delete dbManager;
}

void TestDBManager::initTestCase()
{
    dbManager = new DBManager("localhost", "admin", 3306);
    dbManager->createNewDB(testDbNanme);
}

void TestDBManager::testNewDBwasCreated()
{
    // Checks whether the test DB was created successfully

    std::vector<QString> databases = dbManager->getDatabases();
    QVERIFY(std::find(databases.begin(), databases.end(), testDbNanme) != databases.end());
}

void TestDBManager::cleanupTestCase()
{
    dbManager->deleteDB(testDbNanme);
    dbManager->closeConnection();
}
