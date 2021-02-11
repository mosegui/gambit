#pragma once

#include "controllerdb.h"
#include <QDialog>
#include <QStringList>
#include <QStringListModel>

namespace Ui {
class ExistingSessionsDialog;
}

class ExistingSessionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExistingSessionsDialog(QWidget *parent = nullptr, ControllerDB *dbManager = nullptr);
    ~ExistingSessionsDialog();

    QStringListModel* model;
    QStringList list;

    QString selectedSession;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_clicked();

private:
    Ui::ExistingSessionsDialog *ui;
};

