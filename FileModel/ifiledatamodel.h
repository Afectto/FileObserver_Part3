#ifndef IFILEDATAMODEL_H
#define IFILEDATAMODEL_H

#include <QString>
#include <QVector>
#include <QPair>

class IFileDataModel {
public:
    virtual ~IFileDataModel() = default;
    virtual void setStrategy(class ISizeCalculationStrategy *strategy) = 0;
    virtual void updateData(const QString &path) = 0;
    virtual const QVector<QPair<QString, QString>> &getData() const = 0;
};
#endif // IFILEDATAMODEL_H
