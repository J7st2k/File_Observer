#ifndef MAPTRANSFORMER_H
#define MAPTRANSFORMER_H
#include <QMap>

class MapTransformer
{
public:
    MapTransformer();
    virtual QMap<QString, int>* GetPercentAndSize(const QMap<QString, int>& map, float border) = 0;
    virtual QMap<QString, QString>* GetPercent(const QMap<QString, int>& map, float border) = 0;
};

class FolderTransformer : public MapTransformer
{
public:
    QMap<QString, int>* GetPercentAndSize(const QMap<QString, int>& map, float border);
    QMap<QString, QString>* GetPercent(const QMap<QString, int>& map, float border);
};

class FileTransformer : public MapTransformer
{
public:
    QMap<QString, int>* GetPercentAndSize(const QMap<QString, int>& map, float border);
    QMap<QString, QString>* GetPercent(const QMap<QString, int>& map, float border);
};

#endif // MAPTRANSFORMER_H
