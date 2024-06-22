#include "mainwindow.h"
#include <QSplitter>
#include <QListView>
#include <QTreeView>
#include <QTextEdit>
#include <QFileSystemModel>
#include <QItemSelectionModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
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

    fileModel = new FileExplorerModel(this, context->GetPercent());
    //fileModel->setFilter(QDir::AllDirs);
    //Показать как дерево, пользуясь готовым видом:

    treeView = new QTreeView();
    treeView->setModel(dirModel);

    StratBox = new QComboBox(parent);
    StratBox->addItem("Folder");
    StratBox->addItem("File");
    StratBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    ViewBox = new QComboBox(parent);
    ViewBox->addItem("Table");
    ViewBox->addItem("Bar");
    ViewBox->addItem("Pie");
    ViewBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    treeView->expandAll();
    tableView = new QTableView;
    tableView->setModel(fileModel);

    QVBoxLayout* v1Layout = new QVBoxLayout(parent);
    v1Layout->addWidget(StratBox);
    v1Layout->addWidget(treeView);

    QVBoxLayout* v2Layout = new QVBoxLayout(parent);
    v2Layout->addWidget(ViewBox);
    v2Layout->addWidget(tableView);

    QHBoxLayout* h1Layout = new QHBoxLayout(parent);
    h1Layout->addLayout(v1Layout);
    h1Layout->addLayout(v2Layout);

    QWidget* win = new QWidget();
    win->setLayout(h1Layout);

    setCentralWidget(win);

    QItemSelectionModel *selectionModel = treeView->selectionModel();


    treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //Выполняем соединения слота и сигнала который вызывается когда осуществляется выбор элемента в TreeView
    QObject::connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::on_selectionChangedSlot);
    QObject::connect(this, &MainWindow::upd_signal, fileModel, &FileExplorerModel::UpdateMap);
    QObject::connect(StratBox, &QComboBox::currentTextChanged, this, &MainWindow::on_StratBoxChanged);
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
        emit upd_signal(context->GetPercent());

        // tableView->setModel(nullptr);
        // delete fileModel;
        // fileModel = new FileExplorerModel(this, context->GetCountPercent(1));
        // tableView->setModel(fileModel);
        // tableView->update();
        // qDebug() << QString(dirModel->filePath(indexs.constFirst()));
        // printMap(context->GetCountPercent(1));
    }

    //TODO: !!!!!
    /*
    Тут простейшая обработка ширины первого столбца относительно длины названия папки.
    Это для удобства, что бы при выборе папки имя полностью отображалась в  первом столбце.
    Требуется доработка(переработка).
    */

    //tableView->setRootIndex(fileModel->setRootPath(filePath));
}

void MainWindow::on_StratBoxChanged(const QString &text)
{
    if(text == "Folder")
        context->setStrategy(std::make_shared<fileStatistics>(), std::make_shared<FolderTransformer>());
    if(text == "File")
        context->setStrategy(std::make_shared<formatStatistics>(), std::make_shared<FileTransformer>());
}

void MainWindow::on_ViewBoxChanged(const QString &text)
{
    if(text == "Folder")
        context->setStrategy(std::make_shared<fileStatistics>(), std::make_shared<FolderTransformer>());
    if(text == "File")
        context->setStrategy(std::make_shared<formatStatistics>(), std::make_shared<FileTransformer>());
}

MainWindow::~MainWindow()
{

}
