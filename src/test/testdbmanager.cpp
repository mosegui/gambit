#include "testdbmanager.h"

/*
 * - Manually create database in preparation function
 *    - List available Dbs and check it is there
 *    - CreateIssue in table and manually check it is there
 *    - Get issue ID and check it is correct
 *    - Get issue title and check it is correct
 *    - Get issue description and check it is correct
 *    - Change issue title and check it changes successfully
 *    - Change issue description and check it changes successfully
 *    - remove issue and check it is not there any more
 * - Manually remove the schema/database
 */


void TestDBManager::testStubPass() {
    QVERIFY(true);
}

void TestDBManager::testStubFail() {
    QVERIFY(false);
}
