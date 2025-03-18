#include "barchart.h"

BarChart::BarChart(QWidget *parent) : AbstractChart(parent) {}

void BarChart::DrawChart(const QMap<QString, qint64> &data) {
    // Удаляем все оси X
    for (auto axis : chart->axes(Qt::Horizontal)) {
        chart->removeAxis(axis);
    }

    // Удаляем все оси Y
    for (auto axis : chart->axes(Qt::Vertical)) {
        chart->removeAxis(axis);
    }

    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Размер файлов");

    QStringList categories;
    for (auto it = data.begin(); it != data.end(); ++it) {
        *set << it.value();
        categories << it.key();
    }

    series->append(set);
    chart->addSeries(series);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
}

void BarChart::DrawLegend() {
    chart->legend()->setVisible(true);
}
