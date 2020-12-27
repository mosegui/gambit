#include "existingsessionsdialog.h"
#include "ui_existingsessionsdialog.h"
#include "dbmanager.h"
#include <QStringListModel>
#include <QStringList>

#include <QDebug>
#include <QSqlQuery>

ExistingSessionsDialog::ExistingSessionsDialog(QWidget *parent, DBManager *dbManager) : QDialog(parent), ui(new Ui::ExistingSessionsDialog)
{
    ui->setupUi(this);

    QStringListModel *model = new QStringListModel();
    QStringList list;

    std::vector<QString> dbs = dbManager->getDatabases();
    for(auto it = dbs.begin(); it != dbs.end(); ++it)
    {
        list.append(*it);
    }

    model->setStringList(list);
    ui->listView->setModel(model);
}

ExistingSessionsDialog::~ExistingSessionsDialog()
{
    delete ui;
}

void ExistingSessionsDialog::on_buttonBox_accepted()
{
    selectedSession = ui->listView->currentIndex().data().toString();
    //selectedSession = selectedSession.mid(0, 3);

    accept();
}

void ExistingSessionsDialog::on_buttonBox_rejected()
{
    rejected();
}
