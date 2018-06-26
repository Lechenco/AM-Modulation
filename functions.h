#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QWidget>
#include <QObject>
#include <QtCharts>

class Functions : public QObject
{
    Q_OBJECT
public:
    explicit Functions(QObject *parent = nullptr);
    void setSeries(QLineSeries *series);
    QLineSeries* cos_signal(double l, double t,double a, double f);
    QLineSeries* mod_am_c(QLineSeries * g, double t, double ac, double fc);
    void dem_am_ac(double t, double ac, double fc);
    void setPhi_AM(QLineSeries * phi_AM);

signals:
    void update();

public slots:
    void doWork();

private:
    QLineSeries *series;
    QLineSeries *phi_AM;
};


#endif // FUNCTIONS_H
