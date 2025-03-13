#ifndef BASESIZECALCULATIONSTRATEGY_H
#define BASESIZECALCULATIONSTRATEGY_H

#include "isizecalculationstrategy.h"
#include "Graph/IFileBrowserObserver.h"

class BaseSizeCalculationStrategy : public ISizeCalculationStrategy {
public:

    // Оставляем чисто виртуальный метод, чтобы класс стал абстрактным
    virtual QVector<QPair<QString, QString>> calculate(const QString &path) = 0;

    //Observer pattern
    // Добавление наблюдателя
    void Attach(IFileBrowserObserver *observer);
    // Удаление наблюдателя
    void Detach(IFileBrowserObserver *observer);
    // Оповещение всех наблюдателей
    void Notify(const QMap<QString, qint64> &data);
protected:
    QVector<IFileBrowserObserver*> observers;

    qint64 calculateSize(const QString &path);
    QVector<QPair<QString, QString>> calculatePercentage(const QMap<QString, qint64>& sizeMap, qint64 totalSize);

};
#endif // BASESIZECALCULATIONSTRATEGY_H
