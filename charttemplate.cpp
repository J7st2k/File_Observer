#include "charttemplate.h"
#include <vector>

ChartTemplate::ChartTemplate() {}

QChart *ChartTemplate::createChart(const QMap<QString, int>& map)
{
    QChart* chart = drawChart(map);
    drawLegend(chart);
    return chart;
}

void ChartTemplate::drawLegend(QChart *chart)
{
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
}

QChart *BarChart::drawChart(const QMap<QString, int>& map)
{
    int k = 0;
    QChart *chart = new QChart();
    if(!chart) return chart;
    std::vector<QBarSet*> barSets;
    QMapIterator<QString, int> i(map);

    while(i.hasNext()) {
        i.next();
        barSets.push_back(new QBarSet(i.key(), chart));
        if(!barSets[k]) return chart;
        *barSets[k] << i.value();
    }

    QBarSeries *series = new QBarSeries(chart);
    if(!series) return chart;
    for(int j = 0; j < barSets.size(); j++) {
        series->append(barSeries[j]);
    }
    chart->addSeries(series);

    return chart;
}
