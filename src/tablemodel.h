#pragma once
#include <QAbstractTableModel>
#include <vector>

using namespace std;

class Tablemodel : public QAbstractTableModel
{
    Q_OBJECT

    public:
        Tablemodel(QObject *parent = nullptr);
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        vector<string> issue_titles;
        vector<string> issue_descriptions;
};

