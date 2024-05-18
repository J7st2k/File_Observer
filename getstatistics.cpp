#include "getstatistics.h"


void GetStatistics::FillMap() {
    p->FillMap();
}

const QMap<QString, QString> &GetStatistics::GetMap() {
    return p->GetMap();
}
