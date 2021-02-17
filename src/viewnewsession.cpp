#include "viewnewsession.h"
//#include "ui_newsession.h"

ViewNewSession::ViewNewSession(QWidget *parent) : QDialog(parent), ui(new Ui::NewSession)
{
    ui->setupUi(this);
}

ViewNewSession::~ViewNewSession()
{
    delete ui;
}

void ViewNewSession::on_buttonBox_rejected()
{
    reject();
}

void ViewNewSession::on_buttonBox_accepted()
{
    sessionName = this->get_newSessionName();
    accept();
}

QString ViewNewSession::get_newSessionName()
{
    QString sessionName = ui->lineEdit->text();
    return sessionName;
}


void ViewNewSession::set_newSessionName(QString name)
{
    /* Method used for testing purposes only. Modifies the content
    of widgets hidden behind the pImpl idiom used by QtCreator for
    implementing visual elements
    */

    ui->lineEdit->setText(name);
}

void ViewNewSession::clickAcceptButton()
{
    /* Method used for testing purposes only. Modifies the content
    of widgets hidden behind the pImpl idiom used by QtCreator for
    implementing visual elements
    */

    ui->buttonBox->accepted();
}
