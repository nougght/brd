#ifndef TABSMODEL_H
#define TABSMODEL_H

#include <QAbstractListModel>

class TabsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TabsModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addItem(const QString &text);
private:
    QStringList _data;
};

#endif // TABSMODEL_H
