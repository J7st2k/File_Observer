#include "adapter.h"

IAdapter::IAdapter() {}

TableAdapter::TableAdapter()
{
    fileModel = new FileExplorerModel();
    tableView = new QTableView();
    tableView->setModel(fileModel);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

TableAdapter::~TableAdapter()
{
    delete fileModel;
    delete tableView;
}

void TableAdapter::UpdateView(const GetStatistics *context, QVBoxLayout* layout, QWidget* wid)
{
    if(!context) return;
    layout->removeWidget(wid);
    wid = tableView;
    fileModel->UpdateMap(context->GetPercent());
    layout->addWidget(wid);
}

PieChartAdapter::PieChartAdapter()
{
    chart = new QChart();
    chartView = new QChartView(chart);
}

PieChartAdapter::~PieChartAdapter()
{
    delete chart;
    delete chartView;
}

void PieChartAdapter::UpdateView(const GetStatistics *context, QVBoxLayout* layout, QWidget* wid)
{
    if(!context) return;
    layout->removeWidget(wid);
    wid = chartView;
    PieChart pie;

    QChart *newchart = pie.createChart(*context->GetPercentAndSize());
    chartView->setChart(newchart);
    delete chart;
    chart = newchart;

    layout->addWidget(wid);
}

BarChartAdapter::BarChartAdapter()
{
    chart = new QChart();
    chartView = new QChartView(chart);
}

BarChartAdapter::~BarChartAdapter()
{
    delete chart;
    delete chartView;
}

void BarChartAdapter::UpdateView(const GetStatistics *context, QVBoxLayout* layout, QWidget* wid)
{
    if(!context) return;
    layout->removeWidget(wid);
    wid = chartView;
    BarChart bar;

    QChart *newchart = bar.createChart(*context->GetPercentAndSize());
    chartView->setChart(newchart);
    delete chart;
    chart = newchart;

    layout->addWidget(wid);
}
