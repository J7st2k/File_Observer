#include "fileexplorermodel.h"

FileExplorerModel::FileExplorerModel(QObject *parent) : QFileSystemModel(parent)
{

}

int FileExplorerModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

int FileExplorerModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return map.count();
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
    if (!index.isValid() || map.count() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole))
    {
    return QVariant();
    }
    QMapIterator<QString, QString> i(map);
    i = GetIterator(i, index.row());
        if (index.column() == 0) {
        return i.key();
    } else if (index.column() == 1) {
        return i.value();
    }
}

QMapIterator<QString, QString> &FileExplorerModel::GetIterator(QMapIterator<QString, QString> &i, int pos) const
{
    int k = 0;
    while(i.hasNext() && k < pos) {
        i.next();
    }
    return i;
}

void FileExplorerModel::UpdateMap(const QMap<QString, QString> &_map)
{
    map = _map;
}
