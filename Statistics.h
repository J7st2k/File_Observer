#ifndef STATISTICS_H
#define STATISTICS_H
#include <QDir>
#include <QMap>
#include <QString>
#include <iostream>

class Statistics
{
protected:
    QMap<QString, QString> map;
    QString core;
public:
    Statistics(const QString& Core):core(Core) {}
    ~Statistics() { map.clear(); }
    virtual void FillMap() = 0;
    const QMap<QString, QString>& GetMap();
};

class fileStatistics : public Statistics
{
public:
    fileStatistics(const QString& Core):Statistics(Core) {}
    void FillMap();
private:
    int CountDir(const QString& path);
};

#endif // STATISTICS_H
