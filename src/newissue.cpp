#include "newissue.h"
#include "ui_newissue.h"

newIssue::newIssue(QWidget *parent) : QDialog(parent), ui(new Ui::newIssue)
{
    ui->setupUi(this);
}

newIssue::~newIssue()
{
    delete ui;
}

void newIssue::on_buttonBox_rejected()
{
    reject();
}

void newIssue::on_buttonBox_accepted()
{
    accept();
}

QString newIssue::get_newIsssueID()
{
    QString issueID = ui->newIssueID->text();
    return issueID;
}


QString newIssue::get_newIsssueTitle()
{
    QString issueTitle = ui->newIssueTitle->text();
    return issueTitle;
}
