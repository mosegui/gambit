#include "dbmanager.h"
#include <QMessageBox>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>

DBManager::DBManager(std::string hostName, std::string dbName, std::string userName, int port)
{
    mDatabase = QSqlDatabase::addDatabase("QMYSQL");
    mDatabase.setHostName(QString::fromStdString(hostName));
    mDatabase.setDatabaseName(QString::fromStdString(dbName));
    mDatabase.setUserName(QString::fromStdString(userName));
    mDatabase.setPort(port);
    bool ok = mDatabase.open();

    if (!ok)
    {
        QMessageBox::critical(nullptr, "Error opening the DB", mDatabase.lastError().text());
        return;
    }
}

void DBManager::updateIssueTitle(std::string issueID, std::string issueTitle)
{
    QString querry = QString::fromStdString("UPDATE overview SET title='" + issueTitle + "' WHERE id='" + issueID + "'");
    QSqlQuery qry(mDatabase);
    qry.exec(querry);
}


QSqlTableModel* DBManager::getTableModel(std::string tableName)
{
    mModel = new QSqlTableModel();
    mModel->setTable(QString::fromStdString(tableName));
    mModel->select();
    return mModel;
}

DBManager::~DBManager()
{
    delete mModel;
}


