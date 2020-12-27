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


void DBManager::createIssue(std::string issueID, std::string issueTitle)
{
    QString overview_querry = QString::fromStdString("INSERT INTO overview(pkey, id, title) VALUES(NULL, '" + issueID + "', '" + issueTitle + "')");
    QString contents_querry = QString::fromStdString("INSERT INTO contents(pkey, id, description) VALUES(NULL, '" + issueID + "', 'default description...')");

    QSqlQuery qry(mDatabase);
    qry.exec(overview_querry);
    qry.exec(contents_querry);
}


void DBManager::removeIssue(std::string issueID)
{
    QString contents_querry = QString::fromStdString("DELETE FROM contents WHERE id='" + issueID + "'");
    QString overview_querry = QString::fromStdString("DELETE FROM overview WHERE id='" + issueID + "'");

    QSqlQuery qry(mDatabase);
    qry.exec(contents_querry);
    qry.exec(overview_querry);
}


QSqlTableModel* DBManager::getTableModel(std::string tableName)
{
    mModel = new QSqlTableModel();
    mModel->setTable(QString::fromStdString(tableName));
    mModel->select();
    return mModel;
}


void DBManager::updateIssueTitle(std::string issueID, std::string issueTitle)
{
    QString querry = QString::fromStdString("UPDATE overview SET title='" + issueTitle + "' WHERE id='" + issueID + "'");
    QSqlQuery qry(mDatabase);
    qry.exec(querry);
}


void DBManager::updateIssueDescription(std::string issueID, std::string issueDescription)
{
    QString querry = QString::fromStdString("UPDATE contents SET description='" + issueDescription + "' WHERE id='" + issueID + "'");
    QSqlQuery qry(mDatabase);
    qry.exec(querry);
}

QString DBManager::getIssueID(std::string rowContent)
{
    QString row_id = QString::fromStdString("SELECT id from overview WHERE pkey='" + rowContent + "' OR id='" + rowContent + "' OR title='" + rowContent + "'");
    return row_id;
}


QString DBManager::getIssueTitle(std::string issueID)
{
    QString issue_title = QString::fromStdString("SELECT title from overview WHERE id='" + issueID + "'");
    return issue_title;
}


QString DBManager::getIssueDescription(std::string issueID)
{
    QString issue_description = QString::fromStdString("SELECT description from contents WHERE id='" + issueID + "'");
    return issue_description;
}


DBManager::~DBManager()
{
    delete mModel;
}


