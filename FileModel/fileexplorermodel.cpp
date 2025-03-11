#include "FileExplorerModel.h"
#include "qfontmetrics.h"
#include <QApplication>
#include <QDebug>

FileExplorerModel::FileExplorerModel(IFileDataModel *model, QObject *parent)
    : QAbstractTableModel(parent), fileDataModel(model) {}

int FileExplorerModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return fileDataModel->getData().size();
}

int FileExplorerModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return 2;
}

QVariant FileExplorerModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= fileDataModel->getData().size()) return QVariant();

    const auto &entry = fileDataModel->getData().at(index.row());

    if (role == Qt::DisplayRole) {
        return index.column() == 0 ? entry.first : entry.second;
    }
    return QVariant();
}

QVariant FileExplorerModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section == 0) return tr("Название");
        if (section == 1) return tr("Используемый объем (%)");
    }
    return QVariant();
}

void FileExplorerModel::setStrategy(ISizeCalculationStrategy *newStrategy) {
    beginResetModel();
    fileDataModel->setStrategy(newStrategy);
    fileDataModel->updateData(""); // Очищаем данные
    endResetModel();
}

void FileExplorerModel::setRootPath(const QString &path) {
    if (path.isEmpty()) return;

    beginResetModel();
    fileDataModel->updateData(path);
    endResetModel();
}

int FileExplorerModel::getMaxColumnWidth() const {
    int maxWidth = 100;
    QFontMetrics metrics(QApplication::font());

    for (const auto &entry : fileDataModel->getData()) {
        int textWidth = metrics.horizontalAdvance(entry.first);
        maxWidth = std::max(maxWidth, textWidth);
    }
    return maxWidth + 20;
}
