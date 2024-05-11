#include <QCoreApplication>
#include <QDir>
#include <iostream>

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
    return a.exec();
}
