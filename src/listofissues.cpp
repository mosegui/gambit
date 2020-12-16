#include "listofissues.h"
#include "ui_listofissues.h"
#include <QTableView>
#include <iostream>
#include <QtDebug>


ListOfIssues::ListOfIssues(QWidget *parent) : QMainWindow(parent), ui(new Ui::ListOfIssues)
{
    ui->setupUi(this);

    dbManager = new DBManager("localhost", "gambit_db", "admin", 3306);
    QSqlTableModel* tableModel = dbManager->getTableModel("overview");

    ui->TableItem->setModel(tableModel);
    ui->TableItem->verticalHeader()->setVisible(false);
    ui->TableItem->horizontalHeader()->setStretchLastSection(true);
    ui->TableItem->setSelectionBehavior(QAbstractItemView::SelectRows);
}

ListOfIssues::~ListOfIssues()
{
    delete dbManager;
    delete ui;
}

/*
void ListOfIssues::on_TableItem_clicked(const QModelIndex &index)
{
    int val = index.row();

    QString title = QString::fromStdString(tablemodel->issue_titles.at(val));
    QString description = QString::fromStdString(tablemodel->issue_descriptions.at(val));

    ui->lineEdit->setText(title);
    ui->textEdit->setText(description);
}
*/
