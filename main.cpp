#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include "getstatistics.h"


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


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QDir myDir;
    QString info;
    //info = myDir.path();
    info = QString("D:\\Games");
    std::cout << "Folders:\n";
    GetStatistics g(std::make_shared<fileStatistics>());
    g.FillMap(info);
    printMap(g.GetMap());
    std::cout << "Formats:\n";
    g.setStrategy(std::make_shared<formatStatistics>());
    g.FillMap(info);
    printMap(g.GetMap());
    return a.exec();
}
