#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    baseLayout = new QGridLayout();
    demod_signal = new QLineSeries();

    //Set Signals
    s = new Functions();
    s->setSeries(demod_signal);
    orig_signal = s->cos_signal(500, 5, 1, 1);
    mod_signal = s->mod_am_c(orig_signal, 5, 10, 50);
    s->setPhi_AM(mod_signal);
    s->dem_am_ac(5, 10, 49);


    //Create Slider
    frequency = new QSlider();
    frequency->setLayoutDirection(Qt::LeftToRight);
    frequency->setOrientation(Qt::Horizontal);
    frequency->setTickInterval(5);
    frequency->setMaximum(100);
    frequency->setValue(40);

    //Create Button
    button = new QPushButton();
    button->setText("Push!");
    button->setFixedSize(80, 30);
    baseLayout->addWidget(button, 4, 0);

    this->setCharts();

    //Set Base Layout
    baseLayout->addWidget(frequency);
    setLayout(baseLayout);

    //Threads connection
    worker = new QThread();
    s->moveToThread(worker);
    connect(worker, &QThread::finished, s, &QObject::deleteLater);
    connect(frequency, &QSlider::valueChanged, s, &Functions::doWork);
    connect(s, &Functions::update, this, &MainWindow::update);

    connect(button, &QPushButton::clicked, s, &Functions::doWork);
    connect(button, &QPushButton::clicked, this, &MainWindow::hiden);

    worker->start();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setCharts(){
    //Set Signal Chart
    chart = new QChart();
    chart->addSeries(orig_signal);
    chart->createDefaultAxes();
    chart->setTheme(QChart::ChartThemeBrownSand);
    chart->legend()->hide();

    //Append Chart on Layout
    QChartView *chartView = new QChartView(chart);
    chartView->setFixedHeight(300);
    chartView->setRenderHint(QPainter::Antialiasing, true);
    baseLayout->addWidget(chartView, 0, 0);
    view << chartView;


    //Set Modulate Signal Chart
    chart = new QChart();
    chart->addSeries(mod_signal);
    chart->createDefaultAxes();
    chart->setTheme(QChart::ChartThemeBrownSand);
    chart->legend()->hide();

    //Append Chart on Layout
    chartView = new QChartView(chart);
    chartView->setFixedHeight(300);
    chartView->setRenderHint(QPainter::Antialiasing, true);
    baseLayout->addWidget(chartView, 1, 0);
    view << chartView;

    //Set Demodulate Signal Chart
    chart = new QChart();
    chart->addSeries(demod_signal);
    chart->createDefaultAxes();
    chart->setTheme(QChart::ChartThemeBrownSand);
    chart->legend()->hide();

    //Append Chart on Layout
    chartView = new QChartView(chart);
    chartView->setFixedHeight(300);
    chartView->setRenderHint(QPainter::Antialiasing, true);
    baseLayout->addWidget(chartView, 2, 0);
    view << chartView;
}

void MainWindow::update(){
   button->show();
   view.at(2)->repaint();
    //demod_signal->clear();
    //for(int i = 0; i < 400; i++){
     //    demod_signal->append(i, 0.3);
   // }
   //view.at(2)->update();
}

void MainWindow::hiden(){
    button->hide();
}
