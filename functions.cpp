#include "functions.h"
#include "fft.cpp"
#include <QtCharts>
#include <QObject>
#include <cmath>
#include <cstdlib>


Functions::Functions(QObject *parent) : QObject(parent)
{

}
//===Generator Cossine Signal====
QLineSeries* Functions::cos_signal(double l, double t, double a, double f){
    double h = t / l; //step in s

    QLineSeries *g = new QLineSeries();

    for(int i = 0; i < l; i++){
        g->append(i*h, a*cos(2*M_PI*f*i*h));     //Generating signal
    }

    return g;
}



//===Amplitute Modulation===
QLineSeries* Functions::mod_am_c(QLineSeries * g, double t, double ac, double fc){

    int l = g->count();
    double h = t / l;            //size of step

    //Matrix Modulation Signal Theta
    double c[l];
    for(int i = 0; i < l; i++){
        c[i] = ac * cos(2*M_PI*fc*i*h);
    }

    QLineSeries *phi_AM = new QLineSeries(); //Return vector
    for(int i = 0; i < l; i++)
       phi_AM->append(i*h, g->at(i).y() * c[i]);

   // this->phi_AM = phi_AM;
    return phi_AM;

}

//===Amplitute Demodulaion====
void Functions::dem_am_ac(double t, double ac, double fc){
    int l = phi_AM->count();
    double h = t / l;

    QLineSeries *aux = this->mod_am_c(phi_AM, t, ac, fc);

    //Copy QLineSeries to vector
    double *signal = (double*) malloc(l * sizeof(double));
    for(int i = 0; i < l; i++)
        signal[i] = aux->at(i).y();

    double *frequency = fourier_transform(signal, l);

    frequency = bandpass_filter(frequency, l, 40, l / t);

    signal = inv_fourier_trasnform(frequency, l);

    //Copy vector to QLineSeries
    for(int i = 0; i < l; i++)
        series->append(i * h, signal[i] / (ac*ac));

    free(aux);
    free(signal);
    free(frequency);
}

//===Thread work function===
void Functions::doWork(int fc){
   series->clear();
   dem_am_ac(5, 10, fc);
   emit update();
}

void Functions::setSeries(QLineSeries *series){
    this->series = series;
}

void Functions::setPhi_AM(QLineSeries *phi_AM){
    this->phi_AM = phi_AM;
}
