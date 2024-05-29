#include "Statistics.h"



int fileStatistics::CountDir(const QString &path)
{
    int res = 0;
    if(path.isEmpty()) return res;
    if(!QFileInfo(path).isDir()) return res;
    QDir dir = path;
    QFileInfoList fileInfo = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folderInfo = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < folderInfo.size(); i++) {
        QFileInfo folderI = folderInfo.at(i);
        res += CountDir(folderI.filePath());
    }
    for (int i = 0; i < fileInfo.size(); i++) {
        QFileInfo fileI = fileInfo.at(i);
        res += fileI.size();
    }
    return res;
}

void fileStatistics::FillMap(QMap<QString, QString>& map, const QString& core)
{
    map.clear();
    float res = 0;
    float overall = CountDir(core);
    if(overall == 0) {
        map.insert("*Current path*", QString("0.00 \%"));
        return;
    }
    if(!QFileInfo(core).isDir()) return;
    QDir dir = core;
    QFileInfoList fileInfo = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folderInfo = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < fileInfo.size(); i++) {
        QFileInfo fileI = fileInfo.at(i);
        res += fileI.size();
    }
    float tmp = res/overall;
    // if(tmp == 1) {
    //     map.insert("*Current path*", QString("100.00 \%"));
    //     return;
    // }
    if (tmp != 0 && tmp < 0.01)
        map.insert("*Current path*", QString("<0.01 \%"));
    else map.insert("*Current path*", QString::number(tmp*100, 'f', 2) + QString(" \%"));
    for (int i = 0; i < folderInfo.size(); i++) {
        QFileInfo folderI = folderInfo.at(i);
        tmp = CountDir(folderI.filePath())/overall;
        if (tmp == 1)
            map.insert(folderI.fileName(), QString("100.00 \%"));
        else if (tmp != 0 && tmp < 0.01)
            map.insert(folderI.fileName(), QString("<0.01 \%"));
        else map.insert(folderI.fileName(), QString::number(tmp*100, 'f', 2) + QString(" \%"));
    }
}

void formatStatistics::FillMap(QMap<QString, QString>& map, const QString& core)
{
    float total = 0;
    float tmp = 0;
    float othr = 0;
    bool flag = false;
    QMap<QString, int> memory;
    map.clear();
    CountFormat(core, memory);
    if(memory.empty()) return;
    QMapIterator<QString, int> i(memory);
    while(i.hasNext()) {
        i.next();
        total += i.value();
    }
    i.toFront();
    if(total == 0) {
        while(i.hasNext()) {
            i.next();
            map.insert(QString("*.") + i.key(), QString("0.00 \%"));
        }
        return;
    }
    while(i.hasNext()) {
        i.next();
        tmp = float(i.value())/total;
        if (tmp < 0.01) {
            othr += tmp;
            flag = true;
        }
        else map.insert(QString("*.") + i.key(), QString::number(tmp*100, 'f', 2) + QString(" \%"));
    }
    if (flag)
        map.insert(QString("Others"), QString::number(othr*100, 'f', 2) + QString(" \%"));
}

void formatStatistics::CountFormat(const QString &path, QMap<QString, int>& memory) {
    if(path.isEmpty()) return;
    if(!QFileInfo(path).isDir()) return;
    QDir dir = path;
    QFileInfoList fileInfo = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folderInfo = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < folderInfo.size(); i++) {
        QFileInfo folderI = folderInfo.at(i);
        CountFormat(folderI.filePath(), memory);
    }
    for (int i = 0; i < fileInfo.size(); i++) {
        QFileInfo fileI = fileInfo.at(i);
        memory[fileI.completeSuffix()] += fileI.size();
    }
}
