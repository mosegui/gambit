#include "newsessiondialog.h"
#include "ui_newsessiondialog.h"

NewSessionDialog::NewSessionDialog(QWidget *parent, DBManager *dbManager) : QDialog(parent), ui(new Ui::NewSessionDialog)
{
    ui->setupUi(this);
}

NewSessionDialog::~NewSessionDialog()
{
    delete ui;
}

void NewSessionDialog::on_buttonBox_rejected()
{
    reject();
}

void NewSessionDialog::on_buttonBox_accepted()
{
    sessionName = ui->lineEdit->text();
    accept();
}
