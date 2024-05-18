#include "getstatistics.h"


GetStatistics::GetStatistics(const std::shared_ptr<Statistics> &stat) {
    if(stat) p = stat;
}

void GetStatistics::FillMap() {
    if(!p) return;
    p->FillMap();
}

const QMap<QString, QString> &GetStatistics::GetMap()
{   if(!p) return QMap<QString, QString> emptyMap;
    return p->GetMap();
}
