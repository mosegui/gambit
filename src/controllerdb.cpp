#include "controllerdb.h"

#include <QMessageBox>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>

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


ControllerDB::ControllerDB(std::string hostName, std::string userName, int port, QString connectionName)
{
    /* Connects to the MySQL server
    */
    mainConnectionName = connectionName;

    this->mDatabase = QSqlDatabase::addDatabase("QMYSQL", connectionName);
    this->mDatabase.setHostName(QString::fromStdString(hostName));
    this->mDatabase.setUserName(QString::fromStdString(userName));
    this->mDatabase.setPort(port);

    bool ok = this->mDatabase.open();

    if (!ok)
    {
        QMessageBox::critical(nullptr, "Error connecting to MySQL engine", this->mDatabase.lastError().text());
        return;
    }
}


std::vector<QString> ControllerDB::getDatabases()
{
    /* Retrieves all the available databases for the MySQL server
    *  and returns them in a vector.
    */

    QSqlQuery qry(this->mDatabase);
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

void ControllerDB::connectToDb(QString dbName)
{
    this->mDatabase.setDatabaseName(dbName);
    this->mDatabase.open();
}


void ControllerDB::closeConnection()
{
    this->mDatabase.close();
}


void ControllerDB::refreshModelView()
{
    this->mModel->select();
}


void ControllerDB::createNewDB(QString dbName)
{
    /* Creates a new Schema/database with all the tables and keys
    *  as needed
    */

    QString query = "SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = '" + dbName + "'";
    QSqlQuery q = this->mDatabase.exec(query);

    if (q.size() == 0){
        this->mDatabase.exec("CREATE DATABASE IF NOT EXISTS " + dbName + ";");
        this->mDatabase.setDatabaseName(dbName);

        QString overview_table_qry = "CREATE TABLE `" + dbName + "`.`overview` (`pkey` INT NOT NULL AUTO_INCREMENT, `id` VARCHAR(45) NULL, `title` VARCHAR(45) NULL, PRIMARY KEY (`pkey`));";
        QString contents_table_qry = "CREATE TABLE `" + dbName + "`.`contents` (`pkey` INT NOT NULL AUTO_INCREMENT, `id` VARCHAR(45) NULL, `description` VARCHAR(2000) NULL, PRIMARY KEY (`pkey`));";
        QString foreign_key_qry = "ALTER TABLE '" + dbName + "`.`contents` ADD CONSTRAINT `fk_id` FOREIGN KEY (`id`) REFERENCES `" + dbName + "`.`overview` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;";

        QSqlQuery qry(this->mDatabase);
        qry.exec(overview_table_qry);
        qry.exec(contents_table_qry);
        qry.exec(foreign_key_qry);
    }
}

void ControllerDB::deleteDB(QString dbName)
{
    /* Deletes a schema/database
    */
    QString query = "DROP DATABASE " + dbName;
    this->mDatabase.exec(query);
}


void ControllerDB::createIssue(std::string issueID, std::string issueTitle)
{
    /* Inserts a new record in both tables of the DB representing a new issue
    */

    QString overview_querry = QString::fromStdString("INSERT INTO overview(pkey, id, title) VALUES(NULL, '" + issueID + "', '" + issueTitle + "')");
    QString contents_querry = QString::fromStdString("INSERT INTO contents(pkey, id, description) VALUES(NULL, '" + issueID + "', 'default description...')");

    QSqlQuery qry(this->mDatabase);
    qry.exec(overview_querry);
    qry.exec(contents_querry);
}


void ControllerDB::removeIssue(std::string issueID)
{
    /* Removes a record in both tables of the DB representing a new issue
    */
    QString contents_querry = QString::fromStdString("DELETE FROM contents WHERE id='" + issueID + "'");
    QString overview_querry = QString::fromStdString("DELETE FROM overview WHERE id='" + issueID + "'");

    QSqlQuery qry(this->mDatabase);
    qry.exec(contents_querry);
    qry.exec(overview_querry);
}


QSqlTableModel* ControllerDB::getTableModel(std::string tableName)
{
    /* Casts the model of a DB table to a QSqlTableModel object
     * and returns it.
    */

    this->mModel = new QSqlTableModel(nullptr, this->mDatabase);
    this->mModel->setTable(QString::fromStdString(tableName));
    this->mModel->select();

    return this->mModel;
}


void ControllerDB::updateIssueTitle(std::string issueID, std::string issueTitle)
{
    /* Replaces the title of an existing issue/record from the
     * "overview" table of a database. The record is located via
     * the provided IssueID.
    */

    QString querry = QString::fromStdString("UPDATE overview SET title='" + issueTitle + "' WHERE id='" + issueID + "'");
    QSqlQuery qry(this->mDatabase);
    qry.exec(querry);
}


void ControllerDB::updateIssueDescription(std::string issueID, std::string issueDescription)
{
    /* Replaces the description of an existing issue/record from the
     * "contents" table of a database. The record is located via
     * the provided IssueID.
    */

    QString querry = QString::fromStdString("UPDATE contents SET description='" + issueDescription + "' WHERE id='" + issueID + "'");
    QSqlQuery qry(this->mDatabase);
    qry.exec(querry);
}

QString ControllerDB::getIssueID(std::string rowContent)
{
    /* Retrieves the ID of an issue/record based on the content of the row
     * selected in the QSqlTableModel object.
    */

    QString id_query = QString::fromStdString("SELECT id from overview WHERE pkey='" + rowContent + "' OR id='" + rowContent + "' OR title='" + rowContent + "'");
    QString issue_id = this->get_query_result(id_query);
    return issue_id;
}


QString ControllerDB::getIssueTitle(std::string issueID)
{
    /* Returns an issue title from the passed issue ID
    */

    QString title_query = QString::fromStdString("SELECT title from overview WHERE id='" + issueID + "'");
    QString issue_title = this->get_query_result(title_query);
    return issue_title;
}


QString ControllerDB::getIssueDescription(std::string issueID)
{
    /* Returns an issue description from the passed issue ID
    */

    QString description_querry = QString::fromStdString("SELECT description from contents WHERE id='" + issueID + "'");
    QString issue_description = this->get_query_result(description_querry);
    return issue_description;
}


QString ControllerDB::get_query_result(QString query)
{
    /* Private method actually runs the queries of the above public methods against the DB
    */

    QSqlQuery qry(this->mDatabase);
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


ControllerDB::~ControllerDB()
{
    delete this->mModel;
}


