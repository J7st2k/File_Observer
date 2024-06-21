#ifndef CHARTTEMPLATE_H
#define CHARTTEMPLATE_H

#include <QChart>
#include <QMap>
#include <QBarSeries>
#include <QBarSet>

class ChartTemplate
{
public:
    ChartTemplate();
    ~ChartTemplate() = default;
    QChart* createChart(const QMap<QString, int>& map);
    virtual QChart* drawChart(const QMap<QString, int>& map) = 0;
    void drawLegend(QChart*);
};

class BarChart : public ChartTemplate
{
public:
    QChart* drawChart(const QMap<QString, int>& map);
};

#endif // CHARTTEMPLATE_H
