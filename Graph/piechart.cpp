#include "piechart.h"

PieChart::PieChart(QWidget *parent) : AbstractChart(parent) {}

void PieChart::DrawChart(const QMap<QString, qint64> &data) {
    QPieSeries *series = new QPieSeries();
    for (auto it = data.begin(); it != data.end(); ++it) {
        series->append(it.key(), it.value());
    }
    chart->addSeries(series);
}

void PieChart::DrawLegend() {
    chart->legend()->setVisible(true);
}
