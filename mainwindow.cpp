#include "mainwindow.h"
#include <QSplitter>
#include <QTreeView>
#include <QTableView>
#include <QFileSystemModel>
#include <QItemSelectionModel>
#include <QStatusBar>
#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>
#include "Strategy/fileliststrategy.h"
#include "Strategy/filetypestrategy.h"
#include "qheaderview.h"
#include "FileModel/FileDataModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Настройки главного окна
    this->setGeometry(100, 100, 1500, 500);
    this->setStatusBar(new QStatusBar(this));
    this->statusBar()->showMessage("Выберите папку...");

    QString homePath = QDir::homePath();

    // Модель дерева каталогов
    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(homePath);

    auto fileDataModel = new FileDataModel(new FileListStrategy());
    // Кастомная модель файлов с поддержкой стратегий
    fileModel = new FileExplorerModel(fileDataModel,this);

    // Виджеты
    treeView = new QTreeView();
    treeView->setModel(dirModel);
    treeView->expandAll();

    tableView = new QTableView;
    tableView->setModel(fileModel);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(1);

    // Верхняя панель с выпадающим списком
    QWidget *topPanel = new QWidget(this);
    QHBoxLayout *topLayout = new QHBoxLayout(topPanel);

    strategyComboBox = new QComboBox(this);
    strategyComboBox->addItem("По файлам");
    strategyComboBox->addItem("По типам");

    topLayout->addWidget(new QLabel("Стратегия:"));
    topLayout->addWidget(strategyComboBox);

    topPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    topPanel->setMaximumHeight(strategyComboBox->sizeHint().height() + 20);

    topPanel->setLayout(topLayout);

    // Splitter с деревом и таблицей
    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(treeView);
    splitter->addWidget(tableView);

    // Добавляем всё в основной layout
    mainLayout->addWidget(topPanel);
    mainLayout->addWidget(splitter);

    // Устанавливаем центральный виджет
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Выбор стратегии
    strategies.append(new FileListStrategy());
    strategies.append(new FileTypeStrategy());

    // Подключение сигналов
    connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::on_selectionChangedSlot);
    connect(strategyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_strategyChanged);

    // Выбор стратегии по умолчанию
    on_strategyChanged(0);
}

void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);

    QModelIndex index = treeView->selectionModel()->currentIndex();
    if (!index.isValid()) return;

    QString filePath = dirModel->filePath(index);
    this->statusBar()->showMessage("Выбранный путь: " + filePath);
    updateTreeViewColumnWidth();
    // Обновляем корневой путь модели файлов
    fileModel->setRootPath(filePath);

    updateColumnWidth();
}

void MainWindow::updateTreeViewColumnWidth()
{
    if (!dirModel || !treeView) return;

    QFontMetrics metrics(treeView->font());

    int maxWidth = 100; // Минимальная ширина
    for (int row = 0; row < dirModel->rowCount(QModelIndex()); ++row) {
        QModelIndex index = dirModel->index(row, 0);
        QString text = dirModel->data(index, Qt::DisplayRole).toString();
        int textWidth = metrics.horizontalAdvance(text) + 40; // Добавляем отступ

        QRect rect = treeView->visualRect(index);
        int indentation = rect.x(); // Учитываем отступ для вложенных элементов

        int totalWidth = textWidth + indentation;
        if (totalWidth > maxWidth) {
            maxWidth = totalWidth;
        }
    }

    treeView->header()->resizeSection(0, maxWidth);
}

void MainWindow::on_strategyChanged(int index)
{
    if (index < 0 || index >= strategies.size()) return;

    ISizeCalculationStrategy *strategy = strategies[index];
    fileModel->setStrategy(strategy);
    QModelIndex selectedIndex = treeView->selectionModel()->currentIndex();
    if (selectedIndex.isValid()) {
        QString selectedPath = dirModel->filePath(selectedIndex);
        fileModel->setRootPath(selectedPath); // Обновляем путь модели файлов
    }

    updateColumnWidth();
}

void MainWindow::updateColumnWidth()
{
    if (!fileModel || !tableView) return;

    int maxWidth = static_cast<FileExplorerModel*>(fileModel)->getMaxColumnWidth();
    tableView->setColumnWidth(0, maxWidth);
}

MainWindow::~MainWindow()
{
    for (auto strategy : strategies) {
        delete strategy;
    }
}
