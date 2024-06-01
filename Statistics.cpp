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

void fileStatistics::FillMap(QMap<QString, int>& map, const QString& core)
{
    map.clear();
    int res = 0;
    if(!QFileInfo(core).isDir()) return;
    QDir dir = core;
    QFileInfoList fileInfo = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList folderInfo = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < fileInfo.size(); i++) {
        QFileInfo fileI = fileInfo.at(i);
        res += fileI.size();
    }
    map.insert(QString("*Current path*"), res);
    for (int i = 0; i < folderInfo.size(); i++) {
        QFileInfo folderI = folderInfo.at(i);
        map.insert(folderI.fileName(), CountDir(folderI.filePath()));
    }
}

void formatStatistics::FillMap(QMap<QString, int>& map, const QString& core)
{

    map.clear();
    CountFormat(core, map);
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
