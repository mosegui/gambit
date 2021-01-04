#include "listofissues.h"
#include "ui_listofissues.h"
#include "newissue.h"
#include "existingsessionsdialog.h"
#include "newsessiondialog.h"

#include <iostream>
#include <QMessageBox>
#include <QSqlRecord>

#include <QDebug>


ListOfIssues::ListOfIssues(QWidget *parent) : QMainWindow(parent), ui(new Ui::ListOfIssues)
{
    /* Configures the aspect and the behavior of the Main Window and sets up the connection
     * with the DB via the DBManager
    */

    ui->setupUi(this);
    dbManager = new DBManager("localhost", "gambit_db", "admin", 3306);
}


ListOfIssues::~ListOfIssues()
{
    delete dbManager;
    delete ui;
}


void ListOfIssues::setUp_tableModel_from_connectedDB()
{
    /* Private method sets content and aspect of a the tableItem
     * object in the main window upon connection to the selected
     * session/DB
    */

    tableModel = dbManager->getTableModel("overview");
    ui->TableItem->setModel(tableModel);
    ui->TableItem->hideColumn(0);
    ui->TableItem->verticalHeader()->setVisible(false);
    ui->TableItem->horizontalHeader()->setStretchLastSection(true);
    ui->TableItem->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void ListOfIssues::on_TableItem_clicked(const QModelIndex &index)
{
    /* For a selected item in the QsqlTableModel it retrieves the issue
     * id, title and description and fills in the corrsponding fields.
    */

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
    /* Opens up a new dialog to specify the id and title of a new issue.
     *
     * Having the new issue be specified through a new dialog and be inserted
     * into the DB (both tables) at once after confirmation is an easy way of
     * not having to keep the content of the QsqTableModel and the Title and
     * Description fields constantly synced, as well as not having to hook into
     * the QsqTableModel db insertion method for also inserting a new record in
     * the contents table.
    */

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
    /* Removes selected issue (records) from both tables in the DB
    */

    QSqlRecord currentItem = tableModel->record(ui->TableItem->currentIndex().row());
    std::string currentItemID = currentItem.value("id").toString().toStdString();

    dbManager->removeIssue(currentItemID);
    tableModel->select();
}


void ListOfIssues::on_lineEdit_editingFinished()
{
    /* Allows for edition of the content of the issue title. Updates the "overview"
     * table in the DB.
    */

    QString title = ui->lineEdit->text();
    dbManager->updateIssueTitle(id.toStdString(), title.toStdString());
    tableModel->select();
}

void ListOfIssues::on_textEdit_textChanged()
{
    /* Allows for edition of the content of the issue description. Updates the "contents"
     * table in the DB.
     *
     * This is very inefficient as this function is called every single time the text is
     * changed, causing too much traffic with the DB. It should be called only when the
     * cursor focus goes away from the TextEdit
     */

    QString description = ui->textEdit->toPlainText();
    dbManager->updateIssueDescription(id.toStdString(), description.toStdString());
    tableModel->select();
}


void ListOfIssues::on_id_field_editingFinished()
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

void ListOfIssues::on_actionOpen_Session_triggered()
{
    /* Summons a dialog listing the existing sessions/DBs in the MySQL server.
     * Upon selection of a session, it connects to it and uses the private
     * method "setUp_tableModel_from_connectedDB" to retrieve its content from
     * the "overview" table and fill the tableItem object.
    */

    int res;
    ExistingSessionsDialog existingSessions(this, dbManager);
    existingSessions.setWindowTitle("Existing Sessions");
    res = existingSessions.exec();

    if (res == QDialog::Rejected)
    {
        return;
    }
    QString session = existingSessions.selectedSession;
    dbManager->connectToDb(session);
    this->setUp_tableModel_from_connectedDB();
}

void ListOfIssues::on_actionNew_Session_triggered()
{
    /* Summons a new dialog for introducing the name of a new session.
     * The new Session is then created by the MySQL server as a new
     * DB/Schema.
    */

    int res;
    NewSessionDialog newSession(this, dbManager);
    newSession.setWindowTitle("New Session");
    res = newSession.exec();

    if (res == QDialog::Rejected)
    {
        return;
    }
    QString sessionName = newSession.sessionName;
    dbManager->createNewDB(sessionName);
}
