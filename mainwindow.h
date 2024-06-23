#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include <QComboBox>
#include "getstatistics.h"
#include "fileexplorermodel.h"
#include "adapter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);
    void on_StratBoxChanged(const QString& text);
    void on_ViewBoxChanged(const QString& text);
public:
    MainWindow(QWidget *parent = 0, GetStatistics *_context = nullptr);
    ~MainWindow();
private:
    QFileSystemModel *dirModel;
    QTreeView *treeView;
    GetStatistics *context;
    QComboBox *StratBox;
    QComboBox *ViewBox;

    QWidget *View;
    IAdapter *adapter;
    QVBoxLayout* v2Layout;

    void printMap(QMap<QString, QString>* map) {
        if(!map) return;
        if(!map->empty()) {
            QMapIterator<QString, QString> i(*map);
            while(i.hasNext()) {
                i.next();
                qDebug() << i.key() << QString(": ") << i.value() << Qt::endl;
            }
        }
    }
};

#endif // MAINWINDOW_H
