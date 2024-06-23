#include "fileexplorermodel.h"

FileExplorerModel::FileExplorerModel(QObject *parent) : QAbstractItemModel(parent)
{

}

QModelIndex FileExplorerModel::index(int row, int column, const QModelIndex &parent) const
{
    if (hasIndex(row, column, parent)) {
        return createIndex(row, column);
    }
    return QModelIndex();
}

QModelIndex FileExplorerModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

int FileExplorerModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

int FileExplorerModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return map.size();
}

QVariant FileExplorerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Vertical) {
        return section;
    }
    if  (section == 0)
        return "Название";
    else if (section == 1)
        return "Проценты";

    return QVariant();
}

QVariant FileExplorerModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid() || map.size() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole))
    {
    return QVariant();
    }
    if (map.isEmpty()) return QVariant();
    QMapIterator<QString, QString> i(map);
    //qDebug() << QString("indexes:  ") + QString::number(index.row()) + QString(" ") + QString::number(index.column());
    MoveIterator(i, index.row());
        if (index.column() == 0) {
        return i.key();
    } else if (index.column() == 1) {
        return i.value();
    }
    return QVariant();
}

void FileExplorerModel::MoveIterator(QMapIterator<QString, QString> &i, int pos) const
{
    int k = 0;
    i.next();
    while(i.hasNext() && k < pos) {
        i.next();
        k++;
    }
}

void FileExplorerModel::UpdateMap(const QMap<QString, QString>* _map)
{
    beginResetModel();
    if(_map)
        map = *_map;
    endResetModel();
}
