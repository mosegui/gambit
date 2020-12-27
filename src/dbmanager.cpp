#include "dbmanager.h"

#include <QMessageBox>
#include <QtSql/QSqlError>
#include <QSqlQuery>

#include <QDebug>

/*
   The DB required for a Gambit session must have the following structure:

   Two tables "overview" and "contents"

       Table: overview
           Columns:
               pkey: INTEGER, AUTO_INCREMENT, PRIMARY_KEY, NOT_NULL
               id	VARCHAR(45), UNIQUE
               title	VARCHAR(45)

       Table: contents
           Columns:
               pkey	INTEGER, AUTO_INCREMENT, PRIMARY_KEY, NOT_NULL
               id	VARCHAR(45), UNIQUE, FOREIGN_KEY from table overview
               description	VARCHAR(2000)
*/


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


std::vector<QString> DBManager::getDatabases()
{
    QSqlQuery qry;
    std::vector<QString> existingDbs;

    QString list_qery = QString::fromStdString("SHOW DATABASES");
    qry.prepare(list_qery);

    if (qry.exec())
    {
        while (qry.next())
        {
            existingDbs.push_back(qry.value(0).toString());
        }
    }

    return existingDbs;
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
    QString id_query = QString::fromStdString("SELECT id from overview WHERE pkey='" + rowContent + "' OR id='" + rowContent + "' OR title='" + rowContent + "'");
    QString issue_id = this->get_query_result(id_query);
    return issue_id;
}


QString DBManager::getIssueTitle(std::string issueID)
{
    QString title_query = QString::fromStdString("SELECT title from overview WHERE id='" + issueID + "'");
    QString issue_title = this->get_query_result(title_query);
    return issue_title;
}


QString DBManager::getIssueDescription(std::string issueID)
{
    QString description_querry = QString::fromStdString("SELECT description from contents WHERE id='" + issueID + "'");
    QString issue_description = this->get_query_result(description_querry);
    return issue_description;
}


QString DBManager::get_query_result(QString query)
{
    /* Private method actually runs the queries of the above public methods against the DB
    */

    QSqlQuery qry;
    QString result;

    qry.prepare(query);

    if (qry.exec())
    {
        while (qry.next())
        {
            result = qry.value(0).toString();
        }
    }

    return result;
}


DBManager::~DBManager()
{
    delete mModel;
}


