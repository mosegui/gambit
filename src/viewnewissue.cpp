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

void ViewNewIssue::set_newIssueID(QString id)
{
    /* Method used for testing purposes only. Modifies the content
    of widgets hidden behind the pImpl idiom used by QtCreator for
    implementing visual elements
    */

    ui->newIssueID->setText(id);
}

void ViewNewIssue::set_newIssueTitle(QString title)
{
    /* Method used for testing purposes only. Modifies the content
    of widgets hidden behind the pImpl idiom used by QtCreator for
    implementing visual elements
    */

    ui->newIssueTitle->setText(title);
}

void ViewNewIssue::clickAcceptButton()
{
    /* Method used for testing purposes only. Modifies the content
    of widgets hidden behind the pImpl idiom used by QtCreator for
    implementing visual elements
    */

    ui->buttonBox->accepted();
}
