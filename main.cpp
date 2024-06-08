#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>
#include <QHeaderView>
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

QMap<QString, QString>* countPercent(const QMap<QString, int>& memory, int type, float border = 0.01) {
    float total = 0;
    float tmp = 0;
    bool flag = false;
    QMap<QString, QString>* map = new QMap<QString, QString>;
    if(!map) return map;
    if(memory.empty()) return map;
    if(border >= 100) border = 0;
    QMapIterator<QString, int> i(memory);
    while(i.hasNext()) {
        i.next();
        total += i.value();
    }
    i.toFront();
    if(type == 2) {
        if(total == 0) {
            while(i.hasNext()) {
                i.next();
                map->insert(QString("*.") + i.key(), QString("0.00 \%"));
            }
            return map;
        }
        float othr = 0;
        while(i.hasNext()) {
            i.next();
            tmp = float(i.value())/total;
            if (tmp < border) {
                othr += tmp;
                flag = true;
            }
            else map->insert(QString("*.") + i.key(), QString::number(tmp*100, 'f', 2) + QString(" \%"));
        }
        if (flag)
            map->insert(QString("Others"), QString::number(othr*100, 'f', 2) + QString(" \%"));
    } else if (type == 1) {
        if(total == 0) {
            map->insert("*Current path*", QString("0.00 \%"));
            return map;
        }
        while(i.hasNext()) {
            i.next();
            tmp = float(i.value())/total;
            if(tmp == 0)
                map->insert(i.key(), QString("0.00 \%"));
            else if(tmp < border)
                map->insert(i.key(), QString("<%1 \%").arg(QString::number(border)));
            else map->insert(i.key(), QString("%1 \%").arg(QString::number(tmp*100, 'f', 2)));
        }
    }
    return map;
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

    GetStatistics g(std::make_shared<fileStatistics>());
    g.FillMap(info);
    // std::cout << "Folders raw:\n";
    // printMap(g.GetMap());
    std::cout << "Folders percent:\n";
    printMap(countPercent(g.GetMap(), 1));


    g.setStrategy(std::make_shared<formatStatistics>());
    g.FillMap(info);
    // std::cout << "Formats raw:\n";
    // printMap(g.GetMap());
    std::cout << "\nFormats percent:\n";
    printMap(countPercent(g.GetMap(), 2));

    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath("D:\\qt\\File_Observer\\tests");
    model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    //Показать как дерево, пользуясь готовым видом:
    QTreeView *tree = new QTreeView();
    tree->setModel(model);
    tree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tree->setRootIndex(model->index("D:\\qt\\File_Observer\\tests"));
    tree->hideColumn(1);
    tree->hideColumn(2);
    tree->hideColumn(3);
    //берем данные только через модель!
    tree->show();
    //Показать как список, пользуясь готовым видом:
    // QListView *list = new QListView();
    // list->setModel(model);
    // list->setRootIndex(model->index(QDir::currentPath()));
    // list->show();
    //так как не размещаем компоненты, будет в новом окне

    return a.exec();
}
