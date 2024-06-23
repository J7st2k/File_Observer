#ifndef CHARTTEMPLATE_H
#define CHARTTEMPLATE_H

#include <QtCharts>
#include <QMap>


class ChartTemplate
{
public:
    ChartTemplate();
    virtual ~ChartTemplate() = default;
    QChart* createChart(const QMap<QString, int>& map);
    virtual QChart* drawChart(const QMap<QString, int>& map) = 0;
    void drawLegend(QChart*);
};

class BarChart : public ChartTemplate
{
public:
    QChart* drawChart(const QMap<QString, int>& map);
};

class PieChart : public ChartTemplate
{
public:
    QChart* drawChart(const QMap<QString, int>& map);
};

#endif // CHARTTEMPLATE_H
