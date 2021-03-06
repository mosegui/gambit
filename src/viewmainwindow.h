#pragma once

#include <QMainWindow>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlDatabase>

#include "ui_mainwindow.h"
#include "controllerdialogs.h"
#include "controllerdb.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ViewMainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        ControllerDB* dbManager;
        ControllerDialogs* dialogsManager;

        ViewMainWindow(QWidget *parent = nullptr);
        ~ViewMainWindow();

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
            Ui::MainWindow *ui;
            QString id, title, description;
            QString pkey;
};
