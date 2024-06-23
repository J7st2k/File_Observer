#include "adapter.h"

IAdapter::IAdapter() {}

TableAdapter::TableAdapter()
{
    fileModel = new FileExplorerModel();
    tableView = new QTableView();
    tableView->setModel(fileModel);
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

    // delete chart;
    // chart = cc.createChart();
    // chartView->setChart(chart);
    // chartView->repaint();
}

void PieChartAdapter::UpdateView(const GetStatistics *context, QVBoxLayout* layout, QWidget* wid)
{
    if(!context) return;
    if(!wid) return;
}

void TableChartAdapter::UpdateView(const GetStatistics *context, QVBoxLayout* layout, QWidget* wid)
{
    if(!context) return;
    if(!wid) return;
}
