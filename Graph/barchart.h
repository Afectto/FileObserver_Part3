#ifndef BARCHART_H
#define BARCHART_H
#include "AbstractChart.h"
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>

class BarChart : public AbstractChart {
protected:
    void DrawChart(const QMap<QString, qint64> &data) override;
    void DrawLegend() override;

public:
    explicit BarChart(QWidget *parent = nullptr);
};

#endif // BARCHART_H
