#ifndef GETSTATISTICS_H
#define GETSTATISTICS_H
#include "Statistics.h"
#include <memory>
#include <stdexcept>

class GetStatistics
{
    QMap<QString, QString> map;
    QString core;
public:
    GetStatistics(QString& Core, const std::shared_ptr<Statistics>& stat);
    ~GetStatistics() = default;
    void setStrategy(const std::shared_ptr<Statistics>& stat);
    void FillMap();
    const QMap<QString, QString>& GetMap();
private:
    std::shared_ptr<Statistics> p;
};

#endif // GETSTATISTICS_H
