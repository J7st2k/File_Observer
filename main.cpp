#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include "Statistics.h"

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
    info = myDir.path();
    info = QString("D:\\Games");

    Statistics* _class = new fileStatistics(info);
    _class->FillMap();
    QMap<QString, QString> map = _class->GetMap();
    std::cout << "Folders:\n";
    printMap(map);
    delete _class;
    _class = new formatStatistics(info);
    _class->FillMap();
    QMap<QString, QString> testmap = _class->GetMap();
    std::cout << "Formats:\n";
    printMap(testmap);
    return a.exec();
}
