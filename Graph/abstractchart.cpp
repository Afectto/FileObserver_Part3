#include "abstractchart.h"

AbstractChart::AbstractChart(QWidget *parent) : QWidget(parent) {
    chart = new QChart();
    chartView = new QChartView(chart);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}

void AbstractChart::CreateChart(const QMap<QString, qint64> &data) {
    chart->removeAllSeries();
    DrawChart(data);
    DrawLegend();
}

QChartView* AbstractChart::GetChartView() const {
    return chartView;
}
