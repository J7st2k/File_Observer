#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H
#include <QFileSystemModel>
#include <QMap>
#include <QObject>

class FileExplorerModel: public QFileSystemModel
{
    Q_OBJECT

    QMapIterator<QString, QString>& GetIterator(QMapIterator<QString, QString>& i, int pos) const;
public:
    FileExplorerModel(QObject *parent = nullptr);
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

public slots:
    void UpdateMap(const QMap<QString, QString>& _map);
private:
    QMap<QString, QString> map;
};

#endif // FILEEXPLORERMODEL_H
