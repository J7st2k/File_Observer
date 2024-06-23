#ifndef GETSTATISTICS_H
#define GETSTATISTICS_H
#include "Statistics.h"
#include "maptransformer.h"
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

    GetStatistics(const std::shared_ptr<Statistics>& stat, const std::shared_ptr<MapTransformer>& mt);
    ~GetStatistics() = default;
    void setStrategy(const std::shared_ptr<Statistics>& stat, const std::shared_ptr<MapTransformer>& mt);
    void FillMap(const QString& Core);
    const QMap<QString, int>& GetMap();
    QMap<QString, QString>* GetCountPercent(float border = 0.01);
    QMap<QString, int>* GetPercentAndSize(float border = 0.01) const;
    QMap<QString, QString>* GetPercent(float border = 0.01) const;
private:
    std::shared_ptr<Statistics> p;
    StrategyType type;
    std::shared_ptr<MapTransformer> MT;
};

#endif // GETSTATISTICS_H
