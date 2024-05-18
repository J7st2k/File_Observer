#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include "getstatistics.h"


void printMap(const QMap<QString, QString> map) {
    QTextStream cout(stdout);
    if(!map.empty()) {
        QMapIterator<QString, QString> i(map);
        while(i.hasNext()) {
            i.next();
            cout << i.key() << QString(": ") << i.value() << Qt::endl;
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
    GetStatistics g(std::make_shared<fileStatistics>(info));
    g.FillMap();
    printMap(g.GetMap());
    std::cout << "Formats:\n";
    g.setStrategy(std::make_shared<formatStatistics>(info));
    g.FillMap();
    printMap(g.GetMap());
    return a.exec();
}
