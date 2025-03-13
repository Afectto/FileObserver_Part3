#include "basesizecalculationstrategy.h"
#include <QDir>
#include <QFileInfoList>

void BaseSizeCalculationStrategy::Attach(IFileBrowserObserver *observer) {
    if (!observers.contains(observer)) {
        observers.append(observer);
    }
}

void BaseSizeCalculationStrategy::Detach(IFileBrowserObserver *observer) {
    if (observers.contains(observer)) {
        observers.removeAll(observer);
    }
}

void BaseSizeCalculationStrategy::Notify(const QMap<QString, qint64> &data) {
    for (auto observer : observers) {
        observer->UpdateDisplay(data);
    }
}

qint64 BaseSizeCalculationStrategy::calculateSize(const QString &path) {
    qint64 size = 0;
    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);

    for (const QFileInfo& fileInfo : list) {
        if (fileInfo.isFile()) {
            size += fileInfo.size();
        } else if (fileInfo.isDir()) {
            size += calculateSize(fileInfo.absoluteFilePath());
        }
    }

    return size;
}

QVector<QPair<QString, QString> > BaseSizeCalculationStrategy::calculatePercentage(const QMap<QString, qint64> &sizeMap, qint64 totalSize) {
    QVector<QPair<QString, QString>> percentageList;

    if (totalSize == 0) {
        percentageList.emplace_back("Directory is empty", "0%");
        return percentageList;
    }

    for (auto it = sizeMap.constBegin(); it != sizeMap.constEnd(); ++it) {
        double percentage = static_cast<double>(it.value()) / totalSize * 100;
        QString percentageStr = (percentage < 0.01 && it.value() > 0) ? "< 0.01%" : QString::number(percentage, 'f', 2) + "%";
        percentageList.emplace_back(it.key(), percentageStr);
    }

    return percentageList;
}
