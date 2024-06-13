#include "fileexplorermodel.h"

FileExplorerModel::FileExplorerModel(QObject *parent)
{

}

int FileExplorerModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}
