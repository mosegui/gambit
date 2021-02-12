#include "viewnewissue.h"

ViewNewIssue::ViewNewIssue(QWidget *parent) : QDialog(parent), ui(new Ui::NewIssue)
{
    ui->setupUi(this);
}

ViewNewIssue::~ViewNewIssue()
{
    delete ui;
}

void ViewNewIssue::on_buttonBox_rejected()
{
    reject();
}

void ViewNewIssue::on_buttonBox_accepted()
{
    accept();
}

QString ViewNewIssue::get_newIsssueID()
{
    QString issueID = ui->newIssueID->text();
    return issueID;
}


QString ViewNewIssue::get_newIsssueTitle()
{
    QString issueTitle = ui->newIssueTitle->text();
    return issueTitle;
}
