#pragma once

#include <QDialog>

namespace Ui {
class newIssue;
}

class viewNewIssue : public QDialog
{
    Q_OBJECT

public:
    explicit viewNewIssue(QWidget *parent = nullptr);
    ~viewNewIssue();

    QString get_newIsssueID();
    QString get_newIsssueTitle();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::newIssue *ui;

};

