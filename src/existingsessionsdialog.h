#pragma once

#include "dbmanager.h"
#include <QDialog>

namespace Ui {
class ExistingSessionsDialog;
}

class ExistingSessionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExistingSessionsDialog(QWidget *parent = nullptr, DBManager *dbManager = nullptr);
    ~ExistingSessionsDialog();

    QString selectedSession;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ExistingSessionsDialog *ui;
};

