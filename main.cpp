#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include "Statistics.h"

void setItems(QString const& path, int level = 0)
{
    QDir const source(path);
    if (!source.exists())
        return;
    QStringList const files = source.entryList(QStringList(), QDir::Files);
    QStringList const folders = source.entryList(QDir::NoDot | QDir::NoDotDot | QDir::Dirs);
    QStringList const all = folders + files;
    for (QString const& name: all)
    {
        QString const fullPathName = path + QDir::separator() + name;
        if (QFileInfo(fullPathName).isDir())
        {
            setItems(fullPathName, level + 1);
            continue;
        }
        qDebug() << "Level " << level << " " << fullPathName;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDir dir; //объявляем объект работы с папками
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    ///устанавливаем фильтр выводимых файлов
    dir.setSorting(QDir::Size | QDir::Reversed); //устанавливаем сортировку "от меньшего к большему"
        QFileInfoList list = dir.entryInfoList(); //получаем список файлов директории
            std::cout << "    Bytes   Filename" << std::endl; //выводим заголовок
    /* в цикле выводим сведения о файлах */
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10).arg(fileInfo.fileName())); //выводим в формате "размер имя"
        std::cout << std::endl; //переводим строку
    }

    QDir myDir;
    QString info, res;
    //myDir.setPath("E:/TestA");
    info = myDir.path();
    QFileInfo fileInfo = info;
    /* Рассмотрим способы обхода содержимого папок на диске.
Предлагается вариант решения, который может быть применен для более сложных задач.
Итак, если требуется выполнить анализ содержимого папки, то необходимо организовать обход
содержимого.
Например:*/
    if (fileInfo.isDir()) {
        /*
Если fileInfo папка, то заходим в нее, чтобы просмотреть находящиеся в ней файлы.
Если нужно просмотреть все файлы, включая все вложенные папки, то нужно организовать
рекурсивный обход.
*/
        QDir dir = fileInfo.dir();
        if (dir.cd(fileInfo.fileName())) {
            /*
Если зашли в папку, то пройдемся по контейнеру QFileInfoList, полученного методом
entryInfoList,
*/
            foreach (QFileInfo inf, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Type)) {
                res += inf.fileName() + QString("---") + QString::number(inf.size()) + QString("\n");
            }
            dir.cdUp();//выходим из папки
        }
    }
    std::cout << qPrintable(res);
    setItems(info);
    Statistics* _class = new fileStatistics(info);
    _class->FillMap();
    QMap<QString, QString> map = _class->GetMap();
    QTextStream cout(stdout);
    if(!map.empty()) {
        QMapIterator<QString, QString> i(map);
        while(i.hasNext()) {
            i.next();
            cout << i.key() << QString(": ") << i.value() << Qt::endl;
        }
    }
    return a.exec();
}
