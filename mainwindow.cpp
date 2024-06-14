#include "mainwindow.h"
#include <QSplitter>
#include <QListView>
#include <QTreeView>
#include <QTextEdit>
#include <QFileSystemModel>
#include <QItemSelectionModel>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QStatusBar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent, GetStatistics *_context)
    : //QWidget(parent)
    QMainWindow(parent)
{
    if (!_context)
        throw std::runtime_error("Error in context pointer");
    context = _context;
    //Устанавливаем размер главного окна
    this->setGeometry(100, 100, 1500, 500);
    this->setStatusBar(new QStatusBar(this));
    this->statusBar()->showMessage("Choosen Path: ");
    QString homePath = QDir::homePath();
    // Определим  файловой системы:
    dirModel =  new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath("D:\\qt\\File_Observer\\tests");

    // fileModel = new QFileSystemModel(this);
    // fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);

    // fileModel->setRootPath(homePath);

    fileModel = new FileExplorerModel(this, context->GetCountPercent(2));
    //Показать как дерево, пользуясь готовым видом:

    treeView = new QTreeView();
    treeView->setModel(dirModel);

    treeView->expandAll();
    QSplitter *splitter = new QSplitter(parent);
    tableView = new QTableView;
    tableView->setModel(fileModel);
    splitter->addWidget(treeView);
    splitter->addWidget(tableView);
    setCentralWidget(splitter);

    QItemSelectionModel *selectionModel = treeView->selectionModel();
    // QModelIndex rootIx = dirModel->index(0, 0, QModelIndex());//корневой элемент

    // QModelIndex indexHomePath = dirModel->index(homePath);
    // QFileInfo fileInfo = dirModel->fileInfo(indexHomePath);

    // /* Рассмотрим способы обхода содержимого папок на диске.
    //  * Предлагается вариант решения, которы может быть применен для более сложных задач.
    //  * Итак, если требуется выполнить анализ содержимого папки, то необходимо организовать обход содержимого. Обход выполняем относительно модельного индекса.
    //  * Например:*/
    // if (fileInfo.isDir()) {
    // 	/*
    // 	 * Если fileInfo папка то заходим в нее, что бы просмотреть находящиеся в ней файлы.
    // 	 * Если нужно просмотреть все файлы, включая все вложенные папки, то нужно организовать рекурсивный обход.
    // 	*/
    // 	QDir dir  = fileInfo.dir();

    // 	if (dir.cd(fileInfo.fileName())) {
    // 		/**
    // 		 * Если зашли в папку, то пройдемся по контейнеру QFileInfoList ,полученного методом entryInfoList,
    // 		 * */

    // 		foreach (QFileInfo inf, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Type)) {
    // 			qDebug() << inf.fileName() << "---" << inf.size();
    // 		}

    // 		dir.cdUp();//выходим из папки
    // 	}
    // }

    // QDir dir = fileInfo.dir();

    // foreach (QFileInfo inf, dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDir::Type)) {

    // 	qDebug() << inf.fileName() << "---" << inf.size();
    // }


    treeView->header()->resizeSection(0, 200);
    //Выполняем соединения слота и сигнала который вызывается когда осуществляется выбор элемента в TreeView
    QObject::connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::on_selectionChangedSlot);
    QObject::connect(this, &MainWindow::upd_signal, fileModel, &FileExplorerModel::UpdateMap);
    //Пример организации установки курсора в TreeView относительно модельного индекса
    QItemSelection toggleSelection;
    QModelIndex topLeft;
    topLeft = dirModel->index(homePath);
    dirModel->setRootPath(homePath);

    toggleSelection.select(topLeft, topLeft);
    selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);
}
//Слот для обработки выбора элемента в TreeView
//выбор осуществляется с помощью курсора

void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    //Q_UNUSED(selected);
    Q_UNUSED(deselected);
    QModelIndex index = treeView->selectionModel()->currentIndex();
    QModelIndexList indexs =  selected.indexes();
    QString filePath = "";

    // Размещаем инфо в statusbar относительно выделенного модельного индекса

    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = dirModel->filePath(ix);
        this->statusBar()->showMessage("Выбранный путь : " + dirModel->filePath(indexs.constFirst()));
        context->FillMap(dirModel->filePath(indexs.constFirst()));
        //emit upd_signal(*context->GetCountPercent(2));

        tableView->setModel(nullptr);
        delete fileModel;
        fileModel = new FileExplorerModel(this, context->GetCountPercent(1));
        tableView->setModel(fileModel);
        tableView->update();
        qDebug() << QString(dirModel->filePath(indexs.constFirst()));
        printMap(context->GetCountPercent(1));
    }

    //TODO: !!!!!
    /*
    Тут простейшая обработка ширины первого столбца относительно длины названия папки.
    Это для удобства, что бы при выборе папки имя полностью отображалась в  первом столбце.
    Требуется доработка(переработка).
    */

    treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->setRootIndex(fileModel->setRootPath(filePath));
}

MainWindow::~MainWindow()
{

}
