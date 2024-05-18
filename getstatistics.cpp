#include "getstatistics.h"


GetStatistics::GetStatistics(QString& Core, const std::shared_ptr<Statistics> &stat):core(Core) {
    if(!stat) throw std::runtime_error("Error in strategy pointer");
    p = stat;
}

void GetStatistics::setStrategy(const std::shared_ptr<Statistics> &stat) {
    if(!stat) throw std::runtime_error("Error in strategy pointer");
    p = stat;
}

void GetStatistics::FillMap() {
    p->FillMap(map, core);
}

const QMap<QString, QString> &GetStatistics::GetMap()
{
    return map;
}
