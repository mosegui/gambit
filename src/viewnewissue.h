#pragma once

#include <QDialog>

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

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::NewIssue *ui;

};

