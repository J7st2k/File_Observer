#include "getstatistics.h"


GetStatistics::GetStatistics(const std::shared_ptr<Statistics> &stat, const std::shared_ptr<MapTransformer>& mt) {
    if(!stat) throw std::runtime_error("Error in strategy pointer");
    if(!mt) throw std::runtime_error("Error in transformer pointer");
    p = stat;
    MT = mt;
}

void GetStatistics::setStrategy(const std::shared_ptr<Statistics> &stat, const std::shared_ptr<MapTransformer>& mt) {
    if(stat) p = stat;
    if(mt) MT = mt;
}

void GetStatistics::FillMap(const QString& Core) {
    p->FillMap(map, Core);
}

const QMap<QString, int> &GetStatistics::GetMap()
{
    return map;
}

QMap<QString, int> *GetStatistics::GetPercentAndSize(float border) const
{
    return MT->GetPercentAndSize(map, border);
}

QMap<QString, QString> *GetStatistics::GetPercent(float border) const
{
    return MT->GetPercent(map, border);
}
