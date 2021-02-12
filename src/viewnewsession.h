#pragma once

#include "controllerdb.h"
#include "ui_newsession.h"
#include <QDialog>

namespace Ui {
class NewSession;
}


class ViewNewSession : public QDialog
{
    Q_OBJECT

public:
    explicit ViewNewSession(QWidget *parent = nullptr);

    ~ViewNewSession();
    QString sessionName;

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();

private:
    Ui::NewSession *ui;
};
