#include <oct.h>
#include <builtin-defun-decls.h>
#include <cstdlib>


double* fourier_transform(double* vet, int n){
    Matrix g = Matrix (1, n);

    //Copy vector to Matrix
    for(int i = 0; i < n; i++)
        g(0, i) = vet[i];

    octave_value_list ori_signal;
    ori_signal(0) = g;

    octave_value_list out = Freal(Ffft(ori_signal)); //Ffft - Function fast fourier transform
    Matrix G = out(0).matrix_value();

    double *frequency = (double*) malloc(n * sizeof(double));

    //Copy final Matrix to vector
    for(int i = 0; i < n; i++)
        frequency[i] = G(0, i);

    return frequency;
}

double* inv_fourier_trasnform(double* vet, int n){
    Matrix G = Matrix (1, n);

    //Copy vector to Matrix
    for(int i = 0; i < n; i++)
        G(0, i) = vet[i];

    octave_value_list frequency;
    frequency(0) = G;

    octave_value_list out = Freal(Fifft(frequency)); //Ffft - Function fast fourier transform
    Matrix g = out(0).matrix_value();

    double *ori_signal = (double*) malloc(n * sizeof(double));

    //Copy final Matrix to vector
    for(int i = 0; i < n; i++)
        ori_signal[i] = g(0, i);

    return ori_signal;

}

double* bandpass_filter(double* g, int n, double bw, double fs){

    double h = 2.0 * fs / n;

    for(int i = 0; i < n; i++)
        if(h * i > bw && h * i < 2* fs - bw)
            g[i] = 0;

    return g;
}
