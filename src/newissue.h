#pragma once

#include <QDialog>

namespace Ui {
class newIssue;
}

class newIssue : public QDialog
{
    Q_OBJECT

public:
    explicit newIssue(QWidget *parent = nullptr);
    ~newIssue();

    QString get_newIsssueID();
    QString get_newIsssueTitle();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::newIssue *ui;

};

