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

    this->setGeometry(100, 100, 1500, 500);
    this->setStatusBar(new QStatusBar(this));
    this->statusBar()->showMessage("Choosen Path: ");
    QString homePath = QDir::homePath();
    // Определим  файловой системы:
    dirModel =  new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath("D:\\qt");

    treeView = new QTreeView(this);
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

    adapter = new TableAdapter();

    QVBoxLayout* v1Layout = new QVBoxLayout(parent);
    v1Layout->addWidget(StratBox);
    v1Layout->addWidget(treeView);

    v2Layout = new QVBoxLayout(parent);
    v2Layout->addWidget(ViewBox);

    QHBoxLayout* h1Layout = new QHBoxLayout(parent);
    h1Layout->addLayout(v1Layout);
    h1Layout->addLayout(v2Layout);

    QWidget* win = new QWidget();
    win->setLayout(h1Layout);

    setCentralWidget(win);

    QItemSelectionModel *selectionModel = treeView->selectionModel();


    treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QObject::connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::on_selectionChangedSlot);
    QObject::connect(StratBox, &QComboBox::currentTextChanged, this, &MainWindow::on_StratBoxChanged);
    QObject::connect(ViewBox, &QComboBox::currentTextChanged, this, &MainWindow::on_ViewBoxChanged);


    QItemSelection toggleSelection;
    QModelIndex topLeft;
    topLeft = dirModel->index(homePath);
    dirModel->setRootPath(homePath);

    toggleSelection.select(topLeft, topLeft);
    selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);
}


void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{

    Q_UNUSED(deselected);
    QModelIndexList indexs =  selected.indexes();
    QString filePath = "";

    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = dirModel->filePath(ix);
        this->statusBar()->showMessage("Выбранный путь : " + dirModel->filePath(indexs.constFirst()));

        context->FillMap(dirModel->filePath(indexs.constFirst()));
        adapter->UpdateView(context, v2Layout, View);
    }
}

void MainWindow::on_StratBoxChanged(const QString &text)
{
    if(text == "Folder") {
        context->setStrategy(std::make_shared<fileStatistics>(), std::make_shared<FolderTransformer>());
        on_selectionChangedSlot(treeView->selectionModel()->selection(), treeView->selectionModel()->selection());
    }
    if(text == "File") {
        context->setStrategy(std::make_shared<formatStatistics>(), std::make_shared<FileTransformer>());
        on_selectionChangedSlot(treeView->selectionModel()->selection(), treeView->selectionModel()->selection());
    }
}

void MainWindow::on_ViewBoxChanged(const QString &text)
{
    if(text == "Table") {
        delete adapter;
        adapter = new TableAdapter();
        on_selectionChangedSlot(treeView->selectionModel()->selection(), treeView->selectionModel()->selection());
    }
    if(text == "Bar") {
        delete adapter;
        adapter = new BarChartAdapter();
        on_selectionChangedSlot(treeView->selectionModel()->selection(), treeView->selectionModel()->selection());
    }
    if(text == "Pie") {
        delete adapter;
        adapter = new PieChartAdapter();
        on_selectionChangedSlot(treeView->selectionModel()->selection(), treeView->selectionModel()->selection());
    }
}

MainWindow::~MainWindow()
{
    delete adapter;
}
