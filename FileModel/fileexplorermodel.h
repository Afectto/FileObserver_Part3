#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H

#include <QFileSystemModel>
#include <QPair>
#include "IFileDataModel.h"

class FileExplorerModel : public QAbstractTableModel {
    Q_OBJECT

private:
    IFileDataModel *fileDataModel;

public:
    explicit FileExplorerModel(IFileDataModel *model, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void setStrategy(ISizeCalculationStrategy *newStrategy);
    void setRootPath(const QString &path);
    int getMaxColumnWidth() const;
};

#endif // FILEEXPLORERMODEL_H
