#include <iostream>
#include <QMessageBox>
#include <QSqlRecord>

#include "viewmainwindow.h"

//#include "viewexistingsessions.h"

#include <QDebug>


ViewMainWindow::ViewMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    /* Configures the aspect and the behavior of the Main Window and sets up the connection
     * with the DB via the DBManager
    */

    ui->setupUi(this);
    this->dbManager = new ControllerDB("localhost", "admin", 3306, "main_connection");
    this->dialogsManager = new ControllerDialogs();
}


ViewMainWindow::~ViewMainWindow()
{
    delete this->dbManager;
    delete this->dialogsManager;
    delete ui;
}


void ViewMainWindow::setUp_tableModel_from_connectedDB()
{
    /* Private method sets content and aspect of a the tableItem
     * object in the main window upon connection to the selected
     * session/DB
    */

    this->dbManager->getTableModel("overview");

    ui->TableItem->setModel(this->dbManager->mModel);
    ui->TableItem->hideColumn(0);
    ui->TableItem->verticalHeader()->setVisible(false);
    ui->TableItem->horizontalHeader()->setStretchLastSection(true);
    ui->TableItem->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void ViewMainWindow::on_TableItem_clicked(const QModelIndex &index)
{
    /* For a selected item in the QsqlTableModel it retrieves the issue
     * id, title and description and fills in the corrsponding fields.
    */

    QString selectedContent = this->dbManager->mModel->data(index).toString();

    id = this->dbManager->getIssueID(selectedContent.toStdString());
    title = this->dbManager->getIssueTitle(id.toStdString());
    description = this->dbManager->getIssueDescription(id.toStdString());

    ui->lineEdit->setText(title);
    ui->id_field->setText(id);
    ui->textEdit->setText(description);
}


void ViewMainWindow::on_buttonNewIssue_clicked()
{
    /* Opens up a new dialog to specify the id and title of a new issue.
     *
     * Having the new issue be specified through a new dialog and be inserted
     * into the DB (both tables) at once after confirmation is an easy way of
     * not having to keep the content of the QsqTableModel and the Title and
     * Description fields constantly synced, as well as not having to hook into
     * the QsqTableModel db insertion method for also inserting a new record in
     * the contents table.
    */

    int res = dialogsManager->openNewIssue(this);

    if (res == QDialog::Rejected)
    {
        this->dbManager->mModel->select();  // refreshes table model
        return;
    }

    QString newIssueID = dialogsManager->getNewIssueID();
    QString newIssueTitle = dialogsManager->getNewIssueTitle();

    this->dbManager->createIssue(newIssueID.toStdString(), newIssueTitle.toStdString());
    this->dbManager->mModel->select();
}

void ViewMainWindow::on_buttonRemoveIssue_clicked()
{
    /* Removes selected issue (records) from both tables in the DB
    */

    QSqlRecord currentItem = this->dbManager->mModel->record(ui->TableItem->currentIndex().row());
    std::string currentItemID = currentItem.value("id").toString().toStdString();

    this->dbManager->removeIssue(currentItemID);
    this->dbManager->mModel->select();
}


void ViewMainWindow::on_lineEdit_editingFinished()
{
    /* Allows for edition of the content of the issue title. Updates the "overview"
     * table in the DB.
    */

    QString title = ui->lineEdit->text();
    this->dbManager->updateIssueTitle(id.toStdString(), title.toStdString());
    this->dbManager->mModel->select();
}

void ViewMainWindow::on_textEdit_textChanged()
{
    /* Allows for edition of the content of the issue description. Updates the "contents"
     * table in the DB.
     *
     * This is very inefficient as this function is called every single time the text is
     * changed, causing too much traffic with the DB. It should be called only when the
     * cursor focus goes away from the TextEdit
     */

    QString description = ui->textEdit->toPlainText();
    this->dbManager->updateIssueDescription(id.toStdString(), description.toStdString());
    this->dbManager->mModel->select();
}


void ViewMainWindow::on_id_field_editingFinished()
{
    /* Summons an error dialog if the user attempts to modify the issue ID of an already
     * created issue.
    */

    QString id = ui->id_field->text();

    if (id != this->id)
    {
        QMessageBox::critical(nullptr, "Issue ID", "Once a story is created, the issue ID cannot be modified.");
        ui->id_field->setText(this->id);
    }
}

void ViewMainWindow::on_actionOpen_Session_triggered()
{
    /* Summons a dialog listing the existing sessions/DBs in the MySQL server.
     * Upon selection of a session, it connects to it and uses the private
     * method "setUp_tableModel_from_connectedDB" to retrieve its content from
     * the "overview" table and fill the tableItem object.
    */

    int res = dialogsManager->openExistingSessions(this, this->dbManager);

    if (res == QDialog::Rejected)
    {
        return;
    }

    QString session = dialogsManager->getSelectedSessionName();
    this->dbManager->connectToDb(session);
    this->setUp_tableModel_from_connectedDB();
}

void ViewMainWindow::on_actionNew_Session_triggered()
{
    /* Summons a new dialog for introducing the name of a new session.
     * The new Session is then created by the MySQL server as a new
     * DB/Schema.
    */

    int res = dialogsManager->openNewSession(this);

    if (res == QDialog::Rejected)
    {
        return;
    }

    QString sessionName = dialogsManager->getNewSessionName();
    this->dbManager->createNewDB(sessionName);
}
