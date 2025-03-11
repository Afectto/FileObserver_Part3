#include "filedatamodel.h"

FileDataModel::FileDataModel(ISizeCalculationStrategy *strategy)
    : strategy(strategy) {}

void FileDataModel::setStrategy(ISizeCalculationStrategy *newStrategy) {
    strategy = newStrategy;
}

void FileDataModel::updateData(const QString &path) {
    if (strategy) {
        fileData = strategy->calculate(path);
    } else {
        fileData.clear();
    }
}

const QVector<QPair<QString, QString> > &FileDataModel::getData() const {
    return fileData;
}
