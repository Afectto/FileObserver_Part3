#ifndef FILEDATAMODEL_H
#define FILEDATAMODEL_H

#include "IFileDataModel.h"
#include "Strategy/ISizeCalculationStrategy.h"

class FileDataModel : public IFileDataModel {
private:
    QVector<QPair<QString, QString>> fileData;
    ISizeCalculationStrategy *strategy;

public:
    explicit FileDataModel(ISizeCalculationStrategy *strategy = nullptr);

    void setStrategy(ISizeCalculationStrategy *newStrategy) override;

    void updateData(const QString &path) override;

    const QVector<QPair<QString, QString>> &getData() const override;
};

#endif // FILEDATAMODEL_H
