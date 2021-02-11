#pragma once

#include "controllerdb.h"
#include <QDialog>

namespace Ui {
class NewSessionDialog;
}


class NewSessionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewSessionDialog(QWidget *parent = nullptr, ControllerDB *dbManager = nullptr);
    // I include the DBManager in the signature bc in the future I will want to check agains the DB if the name of the new session already exists

    ~NewSessionDialog();
    QString sessionName;

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();

private:
    Ui::NewSessionDialog *ui;
};
