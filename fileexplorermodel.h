#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H
#include <QFileSystemModel>

class FileExplorerModel: public QFileSystemModel
{
public:
    FileExplorerModel(QObject *parent = nullptr);
    virtual int columnCount(const QModelIndex &parent) const override;
};

#endif // FILEEXPLORERMODEL_H
