#pragma once

#include "controllerdb.h"
#include <QDialog>
#include <QStringList>
#include <QStringListModel>

#include "ui_existingsessions.h"

namespace Ui {
class ExistingSessions;
}

class ViewExistingSessions : public QDialog
{
    Q_OBJECT

public:
    explicit ViewExistingSessions(QWidget *parent = nullptr, ControllerDB *dbManager = nullptr);
    ~ViewExistingSessions();

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

