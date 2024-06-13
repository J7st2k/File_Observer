#include "getstatistics.h"


GetStatistics::GetStatistics(const std::shared_ptr<Statistics> &stat) {
    if(!stat) throw std::runtime_error("Error in strategy pointer");
    p = stat;
}

void GetStatistics::setStrategy(const std::shared_ptr<Statistics> &stat) {
    if(stat) p = stat;
}

void GetStatistics::FillMap(const QString& Core) {
    p->FillMap(map, Core);
}

const QMap<QString, int> &GetStatistics::GetMap()
{
    return map;
}

QMap<QString, QString> *GetStatistics::GetCountPercent(int type, float border) {
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
    if(type == 2) {
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
    } else if (type == 1) {
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
    }
    return _map;
}
