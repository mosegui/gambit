#include "existingsessionsdialog.h"
#include "ui_existingsessionsdialog.h"
#include "dbmanager.h"

#include <QDebug>
#include <QSqlQuery>

ExistingSessionsDialog::ExistingSessionsDialog(QWidget *parent, DBManager *dbManager) : QDialog(parent), ui(new Ui::ExistingSessionsDialog)
{
    /* Retrieves all the existing DB names from the MySQL server and
     * casts the DB names from a vector to a QStringList object. It then
     * sets the list as the model of a listView object.
    */

    ui->setupUi(this);

    model = new QStringListModel();

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
    accept();
}

void ExistingSessionsDialog::on_buttonBox_rejected()
{
    rejected();
}

void ExistingSessionsDialog::on_pushButton_clicked()
{
    QString toDelete = ui->listView->currentIndex().data().toString();

    QString dbDeletionConnectionName = "deletion_connection";
    DBManager* dbDeletionManager = new DBManager("localhost", "admin", 3306, dbDeletionConnectionName);

    dbDeletionManager->deleteDB(toDelete);
    dbDeletionManager->closeConnection();

    dbDeletionManager->mDatabase = QSqlDatabase();
    dbDeletionManager->mDatabase.removeDatabase(dbDeletionConnectionName);

    delete dbDeletionManager;


    list.removeAll(toDelete);
    model->setStringList(list);
    ui->listView->setModel(model);
}
