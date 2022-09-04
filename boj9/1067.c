#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>

const double PI = 3.14159265358979323846264;

int X[60001];
int Y[60001];

void swap(complex *x, complex *y){
    complex temp = *x;
    *x = *y;
    *y = temp;
}

void FFT(complex *f, int size, int inv){

    for(int i=1,j=0; i<size; i++){
        int index = size/2;
        while(!((j^=index)&index)) index = index/2;
        if(i<j) swap(&f[i], &f[j]);
    }

    for(int l=1; l<size; l*=2){
        double a = (inv?-PI/l:PI/l);
        complex w = cos(a) + sin(a)*I;
        for(int i=0; i<size; i+=(l*2)){
            complex wp = 1.0 + 0.0*I;
            for(int j=0; j<l; j++){
                complex x=f[i+j], y=f[i+j+l]*wp;
                f[i+j] = x+y;
                f[i+j+l] = x-y;
                wp *= w;
            }
        }
    }
    if(inv){
        for(int i=0; i<size; i++){
            f[i] /= size;
        }
    }
}
complex* move(int N){
    
    int size = 1;
    while(size<=N) size *= 2;
    size *= 2;
    
    complex * x = (complex*)malloc(sizeof(complex)*size);
    complex * y = (complex*)malloc(sizeof(complex)*size);
    
    memset(x, 0, sizeof(x));
    memset(y, 0 ,sizeof(y));

    for(int i=0; i<N; i++){
        x[i] = (double)X[i] + 0.0*I;
        x[i+N] = (double)X[i] + 0.0*I;
        
        y[i] = (double)Y[N-1-i] + 0.0*I;
    }

    FFT(x,size,0);
    FFT(y, size, 0);
    
    complex * res = (complex*)malloc(sizeof(complex)*size);

    for(int i=0; i<size; i++){
        res[i] = x[i]*y[i];
      
    }

    FFT(res, size, 1);
    
    return res;
    
}
int main(void){
    int N;
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%d", &X[i]);
    }    
    for(int i=0; i<N; i++){
        scanf("%d", &Y[i]);
    }

    complex *res = move(N);
    
    double largest = -1.0;
    for(int i=0; i<2*N; i++){
        
        if(largest<creal(res[i])){
             largest = creal(res[i]);
        }
    }
    printf("%.0f\n", largest);

}