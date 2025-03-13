#ifndef CHARTADAPTER_H
#define CHARTADAPTER_H
#include "IFileBrowserObserver.h"
#include "AbstractChart.h"

//Adapter - Позволяет диаграммам подписываться на стратегию и обновляться.
class ChartAdapter : public IFileBrowserObserver {
protected:
    AbstractChart *chart;
public:
    explicit ChartAdapter(AbstractChart *chart);
    void UpdateDisplay(const QMap<QString, qint64> &data) override;
    QChartView* GetChartView() const;
};
#endif // CHARTADAPTER_H
