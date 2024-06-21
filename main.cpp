#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>
#include <QHeaderView>
#include <QMainWindow>
#include "getstatistics.h"
#include "mainwindow.h"
#include "charttemplate.h"
#include <QChartView>


void printMap(const QMap<QString, int> map) {
    QTextStream cout(stdout);
    if(!map.empty()) {
        QMapIterator<QString, int> i(map);
        while(i.hasNext()) {
            i.next();
            cout << i.key() << QString(": ") << QString::number(i.value()) << Qt::endl;
        }
    }
}

void printMap(QMap<QString, QString>* map) {
    QTextStream cout(stdout);
    if(!map) return;
    if(!map->empty()) {
        QMapIterator<QString, QString> i(*map);
        while(i.hasNext()) {
            i.next();
            cout << i.key() << QString(": ") << i.value() << Qt::endl;
        }
    }
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString info;

    //Папка пустая
    //info = QString("...\\File_Observer\\tests\\EmptyFolder");

    //Папка содержит пустые типы данных
    //info = QString("...\\File_Observer\\tests\\notEmpty");

    //Папка не пустая и не содержит вложения
    //info = QString("...\\File_Observer\\tests\\folderWithSmth");

    //Папка не пустая и содержит вложения
    //info = QString("D:\\qt\\File_Observer\\tests");

    //Папка пустая и содержит вложения
    //info = QString("...\\File_Observer\\tests\\folderWithNothing");

    info = QString("D:\\qt\\File_Observer\\tests\\Equal");
    GetStatistics g(std::make_shared<fileStatistics>(), GetStatistics::FOLDER);
    g.FillMap(info);
    // // std::cout << "Folders raw:\n";
    // // printMap(g.GetMap());
    // std::cout << "Folders percent:\n";
    // printMap(g.GetCountPercent());


    // g.setStrategy(std::make_shared<formatStatistics>(), GetStatistics::FILE);
    // g.FillMap(info);
    // // std::cout << "Formats raw:\n";
    // // printMap(g.GetMap());
    // std::cout << "\nFormats percent:\n";
    // printMap(g.GetCountPercent());

    // g.setStrategy(std::make_shared<fileStatistics>(), GetStatistics::FOLDER);

    //MainWindow w(0, &g);
    //w.show();

    QMainWindow window;
    PieChart cc;
    QChartView *chartView = new QChartView(cc.createChart(g.GetMap()));
    window.setCentralWidget(chartView);
    window.show();
    return a.exec();
}
