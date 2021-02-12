#include "controllerdialogs.h"

ControllerDialogs::~ControllerDialogs()
{
    delete newissue;
    delete newsession;
}

int ControllerDialogs::openNewIssue(QWidget *caller_widget) {

    this->newissue = new ViewNewIssue(caller_widget);
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
