#include "chartadapter.h"

ChartAdapter::ChartAdapter(AbstractChart *chart) : chart(chart) {}

void ChartAdapter::UpdateDisplay(const QMap<QString, qint64> &data) {
    chart->CreateChart(data);
}

QChartView* ChartAdapter::GetChartView() const {
    return chart->GetChartView();
}
