#ifndef ABSTRACTCHART_H
#define ABSTRACTCHART_H
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QWidget>
#include <QVBoxLayout>

//Template Method - Определяет общий алгоритм создания диаграммы
class AbstractChart : public QWidget {
    Q_OBJECT
protected:
    QChart *chart;
    QChartView *chartView;

    virtual void DrawChart(const QMap<QString, qint64> &data) = 0;
    virtual void DrawLegend() = 0;

public:
    explicit AbstractChart(QWidget *parent = nullptr);
    virtual ~AbstractChart() = default;

    void CreateChart(const QMap<QString, qint64> &data);
    QChartView* GetChartView() const;
};

#endif // ABSTRACTCHART_H
