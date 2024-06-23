#ifndef ADAPTER_H
#define ADAPTER_H
#include <QWidget>
#include "charttemplate.h"
#include "getstatistics.h"
#include "fileexplorermodel.h"

class IAdapter
{
public:
    IAdapter();
    virtual ~IAdapter() = default;

    virtual void UpdateView(const GetStatistics* context, QVBoxLayout* layout, QWidget* wid) = 0;
};

class TableAdapter : public IAdapter
{
    FileExplorerModel *fileModel;
    QTableView *tableView;
public:
    TableAdapter();
    ~TableAdapter();
    void UpdateView(const GetStatistics* context, QVBoxLayout* layout, QWidget* wid);
};

class PieChartAdapter : public IAdapter
{
    QChart *chart;
    QChartView *chartView;
public:
    PieChartAdapter();
    void UpdateView(const GetStatistics* context, QVBoxLayout* layout, QWidget* wid);
};

class TableChartAdapter : public IAdapter
{
public:
    TableChartAdapter();
    void UpdateView(const GetStatistics* context, QVBoxLayout* layout, QWidget* wid);
};

#endif // ADAPTER_H
