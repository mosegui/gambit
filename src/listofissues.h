#pragma once
//#include "tablemodel.h"
#include <QMainWindow>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlDatabase>
#include "dbmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ListOfIssues; }
QT_END_NAMESPACE

class ListOfIssues : public QMainWindow
{
    Q_OBJECT

public:
    DBManager* dbManager;

    ListOfIssues(QWidget *parent = nullptr);
    ~ListOfIssues();

private slots:
    // void on_TableItem_clicked(const QModelIndex &index);

private:
    Ui::ListOfIssues *ui;
};
