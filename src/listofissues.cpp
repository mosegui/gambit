#include "listofissues.h"
#include "ui_listofissues.h"
//#include "tablemodel.h"
#include <QTableView>
#include <iostream>
#include <QtDebug>

ListOfIssues::ListOfIssues(QWidget *parent) : QMainWindow(parent), ui(new Ui::ListOfIssues)
{
    ui->setupUi(this);

    ui->TableItem->setModel(tablemodel);
    ui->TableItem->show();
    ui->TableItem->verticalHeader()->setVisible(false);
    ui->TableItem->horizontalHeader()->setStretchLastSection(true);
    ui->TableItem->setSelectionBehavior(QAbstractItemView::SelectRows);


}

ListOfIssues::~ListOfIssues()
{
    delete tablemodel;
    delete ui;
}


void ListOfIssues::on_TableItem_clicked(const QModelIndex &index)
{
    int val = index.row();

    QString title = QString::fromStdString(tablemodel->issue_titles.at(val));
    QString description = QString::fromStdString(tablemodel->issue_descriptions.at(val));

    ui->lineEdit->setText(title);
    ui->textEdit->setText(description);
}
