#pragma once

#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlDatabase>


class DBManager
{
    public:
        QSqlTableModel* mModel;
        QSqlDatabase mDatabase;

        DBManager(std::string, std::string, std::string, int);
        ~DBManager();

        QSqlTableModel* getTableModel(std::string);

        void updateIssueTitle(std::string issueID, std::string issueTitle);
        void updateIssueDescription(std::string issueID, std::string issueDescription);
        void createIssue(std::string issueID, std::string issueTitle);
        void removeIssue(std::string issueID);
        QString getIssueID(std::string rowContent);
        QString getIssueTitle(std::string issueID);
        QString getIssueDescription(std::string issueID);
        std::vector<QString> getDatabases();
        void connectToDb(QString DbName);
        void createNewDB(QString dbName);

    private:
        QString get_query_result(QString query);
};

