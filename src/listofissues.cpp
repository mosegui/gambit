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

    QString pkey_qry, title_qry, id_qry, description_qry;

    id_qry = "SELECT id from overview WHERE pkey='" + selectedContent + "' OR id='" + selectedContent + "' OR title='" + selectedContent + "'";
    id = this->get_query_result(id_qry);

    title_qry = "SELECT title from overview WHERE id='" + id + "'";
    title = this->get_query_result(title_qry);

    description_qry = "SELECT description from contents WHERE id='" + id + "'";
    description = this->get_query_result(description_qry);

    pkey_qry = "SELECT pkey from overview WHERE id='" + id + "'";
    pkey = this->get_query_result(pkey_qry);

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

    qDebug() << "++++++" << newIssueID << ", " << newIssueTitle;

    QSqlQuery qry;
    qry.exec("INSERT INTO overview(pkey, id, title) VALUES(" + QString::fromStdString(std::to_string(tableModel->rowCount()+1)) + ", '" + newIssueID + "', '" + newIssueTitle + "')");
    qry.exec("INSERT INTO contents(pkey, id, description) VALUES(" + QString::fromStdString(std::to_string(tableModel->rowCount()+1)) + ", '" + newIssueID + "', 'default description...')");
    tableModel->select();
}

void ListOfIssues::on_buttonRemoveIssue_clicked()
{ 
    QSqlQuery qry;

    QSqlRecord currentItem = tableModel->record(ui->TableItem->currentIndex().row());
    QString currentItemID = currentItem.value("id").toString();

    qry.exec();
    qry.exec("DELETE FROM contents WHERE id='" + currentItemID + "'");
    qry.exec("DELETE FROM overview WHERE id='" + currentItemID + "'");
    tableModel->select();
}


void ListOfIssues::on_textEdit_textChanged()
{
    /*This is very inefficient as this function is called every single time the text is
     * changed, causing too much traffic with the DB. It should be called only when the
     * cursor focus goes away from the TextEdit
     */

    QSqlQuery qry;
    QString description = ui->textEdit->toPlainText();

    qry.exec("UPDATE contents SET description='" + description + "' WHERE id='" + id + "'");
}

void ListOfIssues::on_lineEdit_editingFinished()
{
    QSqlQuery qry;
    QString title = ui->lineEdit->text();

    qry.exec("UPDATE overview SET title='" + title + "' WHERE id='" + id + "'");
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
