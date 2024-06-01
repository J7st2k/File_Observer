#ifndef STATISTICS_H
#define STATISTICS_H
#include <QDir>
#include <QMap>
#include <QString>
#include <iostream>

class Statistics
{
public:
    ~Statistics() = default;
    virtual void FillMap(QMap<QString, int>& map, const QString& core) = 0;
};

class fileStatistics : public Statistics
{
public:
    ~fileStatistics() = default;
    void FillMap(QMap<QString, int>& map, const QString& core);
private:
    int CountDir(const QString& path);
};

class formatStatistics : public Statistics
{
public:
    ~formatStatistics() = default;
    void FillMap(QMap<QString, int>& map, const QString& core);
private:
    void CountFormat(const QString &path, QMap<QString, int>& memory);
};

#endif // STATISTICS_H
