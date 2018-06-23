#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtCharts>
#include <QSlider>
#include "functions.h"
#include <QThread>

class MainWindow : public QWidget
{
    Q_OBJECT
    QThread interface, worker;

public slots:
    void update();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setCharts();

private:
    Functions *s;
    QSlider *frequency;
    QChart *chart;
    QLineSeries *orig_signal, *mod_signal, *demod_fequency, *demod_signal;
    QList<QChartView* > view;
    QGridLayout *baseLayout;    //Aplication Layout
    QPushButton *button;

};

#endif // MAINWINDOW_H
