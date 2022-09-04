#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

const double PI = 3.14159265358979323846264;
int prime[1000001];

void moshiggang(){

    for(int i=2; i<=1000000; i++){
        if(prime[i]==-1){
            prime[i] = 1;
            
            for(int j=2; j*i<=1000000; j++){
                prime[j*i] = 0;
            }
        }
    }
}

int isPrime(int N){
    return prime[N];
}

void swap(complex *x, complex *y){
    complex temp = *x;
    *x = *y;
    *y = temp;
}

void FFT(complex *f, int size, int inv){
    
    for(int i=1, j=0; i<size; i++){
        int b = size/2;
        while(!((j^=b)&b)) b /= 2;
        if(i<j) swap(&f[i], &f[j]);
    }

    for(int l=1; l<size; l*=2){
        double a = (inv?-PI/l:PI/l);
        complex w = cos(a) + sin(a)*I;
        for(int i=0; i<size; i+=(l*2)){
            complex wp = 1.0 + 0.0*I;
            for(int j=0; j<l; j++){
                complex x = f[i+j], y = wp*f[i+j+l];
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
complex * lmoang(int n){

    int size =1;
    while(size<=n) size*=2;
    
    size*=4;

    complex *x = (complex*)malloc(sizeof(complex)*size);
    complex *y = (complex*)malloc(sizeof(complex)*size);

    memset(x, 0 ,sizeof(x));
    memset(y, 0, sizeof(y));

    for(int i=3; i<=n; i++){
        if(isPrime(i)) x[i] = 1.0 +0.0*I;
    }
    for(int i=2; i<=n; i++){
        if(isPrime(i)) y[2*i] = 1.0 +0.0*I;
    }

    FFT(x, size, 0);
    FFT(y, size, 0);

    complex *res = (complex*)malloc(sizeof(complex)*size);
    for(int i=0; i<size; i++){
        res[i] = x[i]*y[i];
    }
    FFT(res, size, 1);

    return res;
}

int main(void){

    int T;
    scanf("%d", &T);
    memset(prime, -1, sizeof(prime));
    moshiggang();
    complex *res = lmoang(1000000);
    
    while(T--){
        int N;
        scanf("%d", &N);
        printf("%d\n", (int)round(creal(res[N])));           
    }
}