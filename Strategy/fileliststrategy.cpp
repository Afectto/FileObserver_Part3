#include "fileliststrategy.h"


QVector<QPair<QString, QString>> FileListStrategy::calculate(const QString &path) {
    QDir dir(path);
    if (!dir.exists()) {
        qWarning() << "Directory does not exist.";
        return {};
    }

    QFileInfoList list = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
    QMap<QString, qint64> sizeMap;
    qint64 totalSize = 0;

    for (const QFileInfo& fileInfo : list) {
        qint64 fileSize = this->calculateSize(fileInfo.absoluteFilePath());
        totalSize += fileSize;
        QString type = fileInfo.isDir() ? "[DIR] " + fileInfo.fileName() : "[FILE] " + fileInfo.fileName();
        sizeMap[type] = fileSize;
    }

    Notify(sizeMap);
    return calculatePercentage(sizeMap, totalSize);
}
