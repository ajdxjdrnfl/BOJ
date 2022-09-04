#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>

const double PI = 3.14159265358979323846264;


int up[60001];
int mid[60001];
int down[60001];

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
complex* needle(int a, int c){

    
    int size = 1;
    while(size<=120001) size*=2;
    

    complex *x = (complex*)malloc(sizeof(complex)*size);
    complex *y = (complex*)malloc(sizeof(complex)*size);

    memset(x, 0 ,sizeof(x));
    memset(y, 0 ,sizeof(y));
    
    for(int i=0; i<a; i++){
        x[up[i]+30000] += 1.0;
    }
    for(int i=0; i<c; i++){
        y[down[i]+30000] += 1.0;
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

    int a,b,c;
    scanf("%d", &a);
    for(int i=0; i<a; i++){
        scanf("%d", &up[i]);
    }
    scanf("%d", &b);
    for(int i=0; i<b; i++){
        scanf("%d", &mid[i]);
    }
    scanf("%d", &c);
    for(int i=0; i<c; i++){
        scanf("%d", &down[i]);
    }
    
    complex *res = needle(a,c);
    int ans =0;
    for(int i=0; i<b; i++){
        int index = mid[i]*2+60000;
        
        if(creal(res[index])>0) {
            ans+= (int)round(creal(res[index]));
            
        }
    }
    printf("%d\n", ans);
}