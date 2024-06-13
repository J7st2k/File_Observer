#ifndef GETSTATISTICS_H
#define GETSTATISTICS_H
#include "Statistics.h"
#include <memory>
#include <stdexcept>

class GetStatistics
{
    QMap<QString, int> map;
public:
    GetStatistics(const std::shared_ptr<Statistics>& stat);
    ~GetStatistics() = default;
    void setStrategy(const std::shared_ptr<Statistics>& stat);
    void FillMap(const QString& Core);
    const QMap<QString, int>& GetMap();
    QMap<QString, QString>* GetCountPercent(int type, float border = 0.01);
private:
    std::shared_ptr<Statistics> p;
};

#endif // GETSTATISTICS_H
