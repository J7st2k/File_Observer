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

    fileModel = new FileExplorerModel(this, context->GetCountPercent());
    fileModel->setFilter(QDir::AllDirs);
    //Показать как дерево, пользуясь готовым видом:

    treeView = new QTreeView();
    treeView->setModel(dirModel);

    box = new QComboBox(parent);
    box->addItem("Folder");
    box->addItem("File");
    box->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    treeView->expandAll();
    QSplitter *hsplitter = new QSplitter(parent);
    tableView = new QTableView;
    tableView->setModel(fileModel);
    hsplitter->addWidget(treeView);
    hsplitter->addWidget(tableView);

    QSplitter *vsplitter = new QSplitter(Qt::Vertical, parent);
    vsplitter->addWidget(box);
    vsplitter->addWidget(hsplitter);


    // QVBoxLayout* layout = new QVBoxLayout(this);
    // layout->addWidget(box);
    // layout->addWidget(splitter);
    // layout->addStretch();

    setCentralWidget(vsplitter);

    QItemSelectionModel *selectionModel = treeView->selectionModel();


    treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //Выполняем соединения слота и сигнала который вызывается когда осуществляется выбор элемента в TreeView
    QObject::connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::on_selectionChangedSlot);
    QObject::connect(this, &MainWindow::upd_signal, fileModel, &FileExplorerModel::UpdateMap);
    QObject::connect(box, &QComboBox::currentTextChanged, this, &MainWindow::on_boxChanged);
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
    //QModelIndex index = treeView->selectionModel()->currentIndex();
    QModelIndexList indexs =  selected.indexes();
    QString filePath = "";

    // Размещаем инфо в statusbar относительно выделенного модельного индекса

    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = dirModel->filePath(ix);
        this->statusBar()->showMessage("Выбранный путь : " + dirModel->filePath(indexs.constFirst()));
        context->FillMap(dirModel->filePath(indexs.constFirst()));
        emit upd_signal(context->GetCountPercent());

        // tableView->setModel(nullptr);
        // delete fileModel;
        // fileModel = new FileExplorerModel(this, context->GetCountPercent(1));
        // tableView->setModel(fileModel);
        // tableView->update();
        //qDebug() << QString(dirModel->filePath(indexs.constFirst()));
        //printMap(context->GetCountPercent(1));
    }

    //TODO: !!!!!
    /*
    Тут простейшая обработка ширины первого столбца относительно длины названия папки.
    Это для удобства, что бы при выборе папки имя полностью отображалась в  первом столбце.
    Требуется доработка(переработка).
    */

    tableView->setRootIndex(fileModel->setRootPath(filePath));
}

void MainWindow::on_boxChanged(const QString &text)
{
    if(text == "Folder")
        context->setStrategy(std::make_shared<fileStatistics>(), GetStatistics::FOLDER);
    if(text == "File")
        context->setStrategy(std::make_shared<formatStatistics>(), GetStatistics::FILE);
}

MainWindow::~MainWindow()
{

}
