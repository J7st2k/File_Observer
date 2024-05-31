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
