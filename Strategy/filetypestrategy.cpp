#include "filetypestrategy.h"
#include <QDir>
#include <QMap>
#include <QFileInfoList>
#include <QDebug>

QVector<QPair<QString, QString>> FileTypeStrategy::calculate(const QString &path)
{
    QDir dir(path);
    if (!dir.exists()) {
        qWarning() << "Directory does not exist.";
        return {};
    }

    QMap<QString, qint64> sizeMap;
    qint64 totalSize = 0;

    QFileInfoList list = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
    for (const QFileInfo& fileInfo : list) {
        if (fileInfo.isFile()) {
            QString fileType = fileInfo.suffix().isEmpty() ? "[No Extension]" : "*." + fileInfo.suffix();
            sizeMap[fileType] += fileInfo.size();
            totalSize += fileInfo.size();
        } else if (fileInfo.isDir()) {
            qint64 dirSize = calculateSize(fileInfo.absoluteFilePath());
            sizeMap["[DIR]"] += dirSize;
            totalSize += dirSize;
        }
    }

    if (totalSize == 0) {
        qInfo() << "Directory is empty.";
        return {};
    }

    QVector<QPair<QString, QString>> displayList;
    for (auto it = sizeMap.constBegin(); it != sizeMap.constEnd(); ++it) {
        double percentage = static_cast<double>(it.value()) / totalSize * 100;
        QString percentageStr = (percentage < 0.01 && it.value() > 0) ? "< 0.01%" : QString::number(percentage, 'f', 2) + "%";
        displayList.emplace_back(it.key(), percentageStr);
    }

    Notify(sizeMap);
    return displayList;
}
