#pragma once

#include <QMainWindow>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlDatabase>
#include "controllerdb.h"
#include "newissue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ListOfIssues; }
QT_END_NAMESPACE

class ListOfIssues : public QMainWindow
{
    Q_OBJECT

    friend class TestMainWindow;

    public:
        ControllerDB* dbManager;
        newIssue* newissue;

        ListOfIssues(QWidget *parent = nullptr);
        ~ListOfIssues();

    private slots:
        void on_TableItem_clicked(const QModelIndex &index);
        void on_buttonNewIssue_clicked();
        void on_buttonRemoveIssue_clicked();
        void on_textEdit_textChanged();
        void on_lineEdit_editingFinished();
        void on_id_field_editingFinished();
        void on_actionOpen_Session_triggered();
        void on_actionNew_Session_triggered();

    private:
            void setUp_tableModel_from_connectedDB();
            Ui::ListOfIssues *ui;
            QString id, title, description;
            QString pkey;
};
