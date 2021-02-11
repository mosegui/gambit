#pragma once

#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlDatabase>


class ControllerDB
{
    public:
        QSqlTableModel* mModel = nullptr;
        QSqlDatabase mDatabase;

        ControllerDB(std::string, std::string, int, QString);
        ~ControllerDB();

        QSqlTableModel* getTableModel(std::string);

        QString mainConnectionName;

        void updateIssueTitle(std::string issueID, std::string issueTitle);
        void updateIssueDescription(std::string issueID, std::string issueDescription);
        void createIssue(std::string issueID, std::string issueTitle);
        void removeIssue(std::string issueID);
        QString getIssueID(std::string rowContent);
        QString getIssueTitle(std::string issueID);
        QString getIssueDescription(std::string issueID);
        std::vector<QString> getDatabases();
        void connectToDb(QString DbName);
        void closeConnection();
        void createNewDB(QString dbName);
        void deleteDB(QString dbName);

    private:
        QString get_query_result(QString query);
};

