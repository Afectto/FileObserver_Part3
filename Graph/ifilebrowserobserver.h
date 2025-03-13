#ifndef IFILEBROWSEROBSERVER_H
#define IFILEBROWSEROBSERVER_H

#include <QMap>
#include <QString>

//Observer Interfase
//Реализуется диаграммами (ChartAdapter), чтобы получать обновления.
class IFileBrowserObserver{
public:
    virtual void UpdateDisplay(const QMap<QString, qint64> &data) = 0;
};
#endif // IFILEBROWSEROBSERVER_H
