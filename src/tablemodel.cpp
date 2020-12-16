#include "tablemodel.h"
// #include "database.h"

Tablemodel::Tablemodel(QObject *parent) : QAbstractTableModel(parent)
{
    string db_path = "/home/mosegui/QtProjects/gambit/db/Daniel.db";
    Database database(db_path, issue_titles, issue_descriptions);
}

int Tablemodel::rowCount(const QModelIndex & /*parent*/) const
{
    return issue_titles.size();
}

int Tablemodel::columnCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

QVariant Tablemodel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    QVariant result;

    switch(role)
    {
    case Qt::DisplayRole:
        if (col == 0)
        {
            return QString::number(row);

        } else
        {
            return QString::fromStdString(issue_titles.at(row));
        }
    }
    return QVariant();
}


QVariant Tablemodel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Issue ID");
        case 1:
            return QString("Issue Title");
        }
    }
    return QVariant();
}
