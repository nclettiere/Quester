#ifndef QUESTMODEL_H
#define QUESTMODEL_H

#include <QAbstractTableModel>
#include <QBrush>
#include <QFont>

class QuestTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    QuestTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // QUESTMODEL_H
