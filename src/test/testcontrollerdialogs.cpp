#include "testcontrollerdialogs.h"


void TestControllerDialogs::initTestCase()
{
    this->mainwindow = new ViewMainWindow();
    mainwindow->setWindowTitle("TEST GAMBIT");
}


TestControllerDialogs::~TestControllerDialogs()
{
    delete mainwindow;
    delete dialogsManager;
}


void TestControllerDialogs::testOpenNewIssue()
{
    this->dialogsManager = new ControllerDialogs();

    this->dialogsManager->openNewIssueNoExecution(this->mainwindow);

    QString expected_id = "RND01";
    QString expected_title = "Random test title";
    this->dialogsManager->newissue->set_newIssueID(expected_id);
    this->dialogsManager->newissue->set_newIssueTitle(expected_title);

    this->dialogsManager->newissue->clickAcceptButton();

    QString newIssueID = dialogsManager->getNewIssueID();
    QString newIssueTitle = dialogsManager->getNewIssueTitle();

    QVERIFY(newIssueID == expected_id);
    QVERIFY(newIssueTitle == expected_title);


}

void TestControllerDialogs::testOpenNewSession()
{
    this->dialogsManager = new ControllerDialogs();

    this->dialogsManager->openNewSessionNoExecution(this->mainwindow);

    QString expectedSessionName = "test_session_schema";

    this->dialogsManager->newsession->set_newSessionName(expectedSessionName);

    this->dialogsManager->newsession->clickAcceptButton();

    QString newSessionName = this->dialogsManager->newsession->get_newSessionName();

    QVERIFY(newSessionName == expectedSessionName);

}
