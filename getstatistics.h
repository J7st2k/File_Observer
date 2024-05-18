#ifndef GETSTATISTICS_H
#define GETSTATISTICS_H
#include "Statistics.h"
#include <memory>

class GetStatistics
{
public:
    GetStatistics(const std::shared_ptr<Statistics>& stat);
    ~GetStatistics() = default;
    void setStrategy(const std::shared_ptr<Statistics>& stat) { if(stat) p = stat; }
    void FillMap();
    const QMap<QString, QString>& GetMap();
private:
    std::shared_ptr<Statistics> p;
};

#endif // GETSTATISTICS_H
