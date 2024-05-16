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

void fileStatistics::FillMap()
{
    map.clear();
    float res = 0;
    if(core.isEmpty()) return;
    if(!QFileInfo(core).isDir()) return;
    float overall = CountDir(core);
    QDir dir = core;
    QFileInfoList fileInfo = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folderInfo = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < fileInfo.size(); i++) {
        QFileInfo fileI = fileInfo.at(i);
        res += fileI.size();
    }
    float tmp = res/overall;
    if (tmp != 0 && tmp < 0.01)
        map.insert("*Current path*", QString("<0.01 \%"));
    else map.insert("*Current path*", QString::number(tmp, 'f', 2) + QString(" \%"));
    for (int i = 0; i < folderInfo.size(); i++) {
        QFileInfo folderI = folderInfo.at(i);
        tmp = CountDir(folderI.filePath())/overall;
        if (tmp != 0 && tmp < 0.01)
            map.insert(folderI.fileName(), QString("<0.01 \%"));
        else map.insert(folderI.fileName(), QString::number(CountDir(folderI.filePath())/overall, 'f', 2) + QString(" \%"));
    }
}

const QMap<QString, QString>& Statistics::GetMap()
{
    return map;
}

