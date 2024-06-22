#include "maptransformer.h"

MapTransformer::MapTransformer() {}


QMap<QString, int> *FolderTransformer::GetPercentAndSize(const QMap<QString, int> &map, float border)
{
    QMap<QString, int>* res = new QMap<QString, int>;
    if(!res) return res;
    QMap<QString, QString>* _map = GetPercent(map, border);
    if(!_map) return res;

    QMapIterator<QString, int> i(map);
    while(i.hasNext()) {
        i.next();
        res->insert(i.key() + QString(" (") + _map->value(i.key()) + QString(")"), i.value());
    }

    delete _map;
    return res;
}

QMap<QString, QString> *FolderTransformer::GetPercent(const QMap<QString, int> &map, float border)
{
    float total = 0;
    float tmp = 0;

    QMap<QString, QString>* _map = new QMap<QString, QString>;
    if(!_map) return _map;
    if(map.empty()) return _map;
    if(border >= 100) border = 0;
    QMapIterator<QString, int> i(map);
    while(i.hasNext()) {
        i.next();
        total += i.value();
    }
    i.toFront();
    if(total == 0) {
        _map->insert("*Current path*", QString("0.00 \%"));
        return _map;
    }
    while(i.hasNext()) {
        i.next();
        tmp = float(i.value())/total;
        if(tmp == 0)
            _map->insert(i.key(), QString("0.00 \%"));
        else if(tmp < border)
            _map->insert(i.key(), QString("<%1 \%").arg(QString::number(border)));
        else _map->insert(i.key(), QString("%1 \%").arg(QString::number(tmp*100, 'f', 2)));
    }

    return _map;
}

QMap<QString, int> *FileTransformer::GetPercentAndSize(const QMap<QString, int> &map, float border)
{
    QMap<QString, int>* res = new QMap<QString, int>;
    if(!res) return res;
    QMap<QString, QString>* _map = GetPercent(map, border);
    if(!_map) return res;

    QMapIterator<QString, int> i(map);
    while(i.hasNext()) {
        i.next();
        res->insert(i.key() + QString(" (") + _map->value(i.key()) + QString(")"), i.value());
    }

    delete _map;
    return res;
}

QMap<QString, QString> *FileTransformer::GetPercent(const QMap<QString, int> &map, float border)
{
    float total = 0;
    float tmp = 0;
    bool flag = false;
    QMap<QString, QString>* _map = new QMap<QString, QString>;
    if(!_map) return _map;
    if(map.empty()) return _map;
    if(border >= 100) border = 0;
    QMapIterator<QString, int> i(map);
    while(i.hasNext()) {
        i.next();
        total += i.value();
    }
    i.toFront();
    if(total == 0) {
        while(i.hasNext()) {
            i.next();
            _map->insert(QString("*.") + i.key(), QString("0.00 \%"));
        }
        return _map;
    }
    float othr = 0;
    while(i.hasNext()) {
        i.next();
        tmp = float(i.value())/total;
        if (tmp < border) {
            othr += tmp;
            flag = true;
        }
        else _map->insert(QString("*.") + i.key(), QString::number(tmp*100, 'f', 2) + QString(" \%"));
    }
    if (flag)
        _map->insert(QString("Others"), QString::number(othr*100, 'f', 2) + QString(" \%"));

    return _map;
}
