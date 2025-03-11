#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include <QComboBox>
#include "FileModel/fileexplorermodel.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
private slots:

    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);
    void on_strategyChanged(int index);

public:
	MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QComboBox *strategyComboBox;
    FileExplorerModel  *fileModel;
    QFileSystemModel *dirModel;
	QTreeView *treeView;
	QTableView *tableView;
    QVector<ISizeCalculationStrategy*> strategies;
    void updateColumnWidth();
    void updateTreeViewColumnWidth();
    int calculateMaxColumnWidth();
};

#endif // MAINWINDOW_H
