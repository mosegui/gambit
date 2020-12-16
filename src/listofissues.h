#pragma once
#include "tablemodel.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ListOfIssues; }
QT_END_NAMESPACE

class ListOfIssues : public QMainWindow
{
    Q_OBJECT

public:
    Tablemodel* tablemodel = new Tablemodel();

    ListOfIssues(QWidget *parent = nullptr);
    ~ListOfIssues();

private slots:
    void on_TableItem_clicked(const QModelIndex &index);

private:
    Ui::ListOfIssues *ui;
};
