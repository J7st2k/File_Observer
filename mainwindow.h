#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include "getstatistics.h"
#include "fileexplorermodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);
signals:
    upd_signal(const QMap<QString, QString>& _map);
public:
    MainWindow(QWidget *parent = 0, GetStatistics *_context = nullptr);
    ~MainWindow();
private:
    FileExplorerModel *fileModel;
    QFileSystemModel *dirModel;
    QTreeView *treeView;
    QTableView *tableView;
    GetStatistics *context;
};

#endif // MAINWINDOW_H