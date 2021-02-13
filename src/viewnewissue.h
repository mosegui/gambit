#pragma once

#include <QDialog>

#include "ui_newissue.h"

namespace Ui {
class NewIssue;
}

class ViewNewIssue : public QDialog
{
    Q_OBJECT

public:
    explicit ViewNewIssue(QWidget *parent = nullptr);
    ~ViewNewIssue();

    QString get_newIsssueID();
    QString get_newIsssueTitle();

    // testing mehtods
    void set_newIssueID(QString);
    void set_newIssueTitle(QString);
    void clickAcceptButton();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::NewIssue *ui;

};

