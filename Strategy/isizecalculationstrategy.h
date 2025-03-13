#ifndef ISIZECALCULATIONSTRATEGY_H
#define ISIZECALCULATIONSTRATEGY_H

#include <QString>
#include "Graph/IFileBrowserObserver.h"


// Интерфейс стратегии для расчета размера директории
class ISizeCalculationStrategy {
public:
    virtual ~ISizeCalculationStrategy() = default;
    virtual QVector<QPair<QString, QString>> calculate(const QString &path) = 0;

    virtual void Attach(IFileBrowserObserver *observer) = 0;
    virtual void Detach(IFileBrowserObserver *observer) = 0;
    virtual void Notify(const QMap<QString, qint64> &data) = 0;
};
#endif // ISIZECALCULATIONSTRATEGY_H
