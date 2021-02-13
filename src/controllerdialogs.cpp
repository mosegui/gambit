#include "controllerdialogs.h"

ControllerDialogs::~ControllerDialogs()
{
    delete newissue;
    delete newsession;
    delete existingsessions;
}

void ControllerDialogs::openNewIssueNoExecution(QWidget *caller_widget) {

    /* Useful standalone for testing functionality of Controller class.
     * Allows using Dialog private attributes but does not execute the
     * dialog object.
     */

    this->newissue = new ViewNewIssue(caller_widget);
}

int ControllerDialogs::openNewIssue(QWidget *caller_widget) {

    ControllerDialogs::openNewIssueNoExecution(caller_widget);
    //this->newissue = new ViewNewIssue(caller_widget);
    int res = newissue->exec();

    return res;
}

QString ControllerDialogs::getNewIssueID() {

    QString issueID = this->newissue->get_newIsssueID();
    return issueID;
}

QString ControllerDialogs::getNewIssueTitle() {

    QString issueTitle = this->newissue->get_newIsssueTitle();    
    return issueTitle;
}

int ControllerDialogs::openNewSession(QWidget *caller_widget) {

    this->newsession = new ViewNewSession(caller_widget);
    newsession->setWindowTitle("New Session");
    int res = newsession->exec();

    return res;
}

QString ControllerDialogs::getNewSessionName() {

    QString sessionName = newsession->sessionName;
    return sessionName;
}

int ControllerDialogs::openExistingSessions(QWidget *caller_widget, ControllerDB *dbManager) {

    this->existingsessions = new ViewExistingSessions(caller_widget, dbManager);
    existingsessions->setWindowTitle("Existing Sessions");
    int res = existingsessions->exec();

    return res;
}

QString ControllerDialogs::getSelectedSessionName() {

    QString selectedSession = existingsessions->selectedSession;
    return selectedSession;
}
