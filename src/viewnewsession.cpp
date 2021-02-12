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
    sessionName = ui->lineEdit->text();
    accept();
}
