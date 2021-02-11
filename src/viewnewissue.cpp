#include "viewnewissue.h"
#include "ui_newissue.h"

viewNewIssue::viewNewIssue(QWidget *parent) : QDialog(parent), ui(new Ui::newIssue)
{
    ui->setupUi(this);
}

viewNewIssue::~viewNewIssue()
{
    delete ui;
}

void viewNewIssue::on_buttonBox_rejected()
{
    reject();
}

void viewNewIssue::on_buttonBox_accepted()
{
    accept();
}

QString viewNewIssue::get_newIsssueID()
{
    QString issueID = ui->newIssueID->text();
    return issueID;
}


QString viewNewIssue::get_newIsssueTitle()
{
    QString issueTitle = ui->newIssueTitle->text();
    return issueTitle;
}
