#include "tabsmodel.h"
#include <QBrush>

TabsModel::TabsModel(QObject *parent)
    : QAbstractListModel{parent}
{}


int TabsModel::rowCount(const QModelIndex &parent) const
{
    return _data.count();
}
QVariant TabsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= _data.count())
        return QVariant();

    // View спрашивает текст для отрисовки
    if (role == Qt::DisplayRole) {
        return _data.at(index.row());
    }

    // Можно задать цвет текста (Role)
    if (role == Qt::ForegroundRole && _data.at(index.row()).contains("Важно")) {
        return QBrush(Qt::red);
    }

    return QVariant();
}
void TabsModel::addItem(const QString &text)
{
    beginInsertRows(QModelIndex(), _data.count(), _data.count());
    _data.append(text);
    endInsertRows();
}
