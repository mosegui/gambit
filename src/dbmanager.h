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
};

