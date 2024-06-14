#ifndef GETSTATISTICS_H
#define GETSTATISTICS_H
#include "Statistics.h"
#include <memory>
#include <stdexcept>

class GetStatistics
{
    QMap<QString, int> map;
public:
    enum StrategyType {
        FOLDER = 1,
        FILE = 2
    };

    GetStatistics(const std::shared_ptr<Statistics>& stat, StrategyType _type);
    ~GetStatistics() = default;
    void setStrategy(const std::shared_ptr<Statistics>& stat, StrategyType _type);
    void FillMap(const QString& Core);
    const QMap<QString, int>& GetMap();
    QMap<QString, QString>* GetCountPercent(float border = 0.01);
private:
    std::shared_ptr<Statistics> p;
    StrategyType type;
};

#endif // GETSTATISTICS_H
