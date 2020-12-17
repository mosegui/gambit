#include "listofissues.h"
#include "ui_listofissues.h"
#include <QTableView>
#include <iostream>
#include <QtDebug>
#include <QSqlQuery>


ListOfIssues::ListOfIssues(QWidget *parent) : QMainWindow(parent), ui(new Ui::ListOfIssues)
{
    ui->setupUi(this);

    dbManager = new DBManager("localhost", "gambit_db", "admin", 3306);
    tableModel = dbManager->getTableModel("overview");

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


QString ListOfIssues::get_query_result(QString query)
{
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


void ListOfIssues::on_TableItem_clicked(const QModelIndex &index)
{
    QString selectedContent = tableModel->data(index).toString();

    QString title_qry, id_qry, description_qry;
    QString id, title, description;

    id_qry = "SELECT id from overview WHERE pkey='" + selectedContent + "' OR id='" + selectedContent + "' OR title='" + selectedContent + "'";
    id = this->get_query_result(id_qry);

    title_qry = "SELECT title from overview WHERE id='" + id + "'";
    title = this->get_query_result(title_qry);

    description_qry = "SELECT description from contents WHERE id='" + id + "'";
    description = this->get_query_result(description_qry);

    ui->lineEdit->setText(title);
    ui->id_field->setText(id);
    ui->textEdit->setText(description);
}
