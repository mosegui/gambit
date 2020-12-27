#include "listofissues.h"
#include "ui_listofissues.h"
#include <QTableView>
#include <iostream>
#include <QtDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include "newissue.h"
#include <QSqlRecord>

ListOfIssues::ListOfIssues(QWidget *parent) : QMainWindow(parent), ui(new Ui::ListOfIssues)
{
    ui->setupUi(this);

    dbManager = new DBManager("localhost", "gambit_db", "admin", 3306);
    tableModel = dbManager->getTableModel("overview");

    ui->TableItem->setModel(tableModel);
    ui->TableItem->hideColumn(0);
    ui->TableItem->verticalHeader()->setVisible(false);
    ui->TableItem->horizontalHeader()->setStretchLastSection(true);

    ui->TableItem->setSelectionBehavior(QAbstractItemView::SelectRows);
}


ListOfIssues::~ListOfIssues()
{
    delete dbManager;
    delete ui;
}


void ListOfIssues::on_TableItem_clicked(const QModelIndex &index)
{
    QString selectedContent = tableModel->data(index).toString();

    id = dbManager->getIssueID(selectedContent.toStdString());
    title = dbManager->getIssueTitle(id.toStdString());
    description = dbManager->getIssueDescription(id.toStdString());

    ui->lineEdit->setText(title);
    ui->id_field->setText(id);
    ui->textEdit->setText(description);
}


void ListOfIssues::on_buttonNewIssue_clicked()
{
    int res;
    newIssue newissue(this);
    res = newissue.exec();

    if (res == QDialog::Rejected)
    {
        tableModel->select();
        return;
    }

    QString newIssueID = newissue.get_newIsssueID();
    QString newIssueTitle = newissue.get_newIsssueTitle();

    dbManager->createIssue(newIssueID.toStdString(), newIssueTitle.toStdString());
    tableModel->select();
}

void ListOfIssues::on_buttonRemoveIssue_clicked()
{ 
    QSqlRecord currentItem = tableModel->record(ui->TableItem->currentIndex().row());
    std::string currentItemID = currentItem.value("id").toString().toStdString();

    dbManager->removeIssue(currentItemID);
    tableModel->select();
}


void ListOfIssues::on_lineEdit_editingFinished()
{
    QString title = ui->lineEdit->text();
    dbManager->updateIssueTitle(id.toStdString(), title.toStdString());
    tableModel->select();
}

void ListOfIssues::on_textEdit_textChanged()
{
    /*This is very inefficient as this function is called every single time the text is
     * changed, causing too much traffic with the DB. It should be called only when the
     * cursor focus goes away from the TextEdit
     */
    QString description = ui->textEdit->toPlainText();
    dbManager->updateIssueDescription(id.toStdString(), description.toStdString());
    tableModel->select();
}


void ListOfIssues::on_id_field_editingFinished()
{
    QString id = ui->id_field->text();

    if (id != this->id)
    {
        QMessageBox::critical(nullptr, "Issue ID", "Once a story is created, the issue ID cannot be modified.");
        ui->id_field->setText(this->id);
    }
}
