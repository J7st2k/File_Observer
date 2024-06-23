#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H
#include <QFileSystemModel>
#include <QMap>
#include <QObject>
#include <QDebug>

class FileExplorerModel: public QAbstractItemModel
{
    Q_OBJECT

    void MoveIterator(QMapIterator<QString, QString>& i, int pos) const;
public:
    FileExplorerModel(QObject *parent = nullptr);
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role) const override;

public slots:
    void UpdateMap(const QMap<QString, QString>* _map);
private:
    QMap<QString, QString> map;
};

#endif // FILEEXPLORERMODEL_H
