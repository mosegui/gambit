#include "controllerdialogs.h"

ControllerDialogs::ControllerDialogs()
{

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
