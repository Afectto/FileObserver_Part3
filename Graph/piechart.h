#ifndef PIECHART_H
#define PIECHART_H
#include "AbstractChart.h"
#include <QtCharts/QPieSeries>

class PieChart : public AbstractChart {
protected:
    void DrawChart(const QMap<QString, qint64> &data) override;
    void DrawLegend() override;

public:
    explicit PieChart(QWidget *parent = nullptr);
};

#endif // PIECHART_H
