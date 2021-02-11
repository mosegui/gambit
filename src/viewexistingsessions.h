#pragma once

#include "controllerdb.h"
#include <QDialog>
#include <QStringList>
#include <QStringListModel>

namespace Ui {
class ExistingSessions;
}

class viewExistingSessions : public QDialog
{
    Q_OBJECT

public:
    explicit viewExistingSessions(QWidget *parent = nullptr, ControllerDB *dbManager = nullptr);
    ~viewExistingSessions();

    QStringListModel* model;
    QStringList list;

    QString selectedSession;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_clicked();

private:
    Ui::ExistingSessions *ui;
};

