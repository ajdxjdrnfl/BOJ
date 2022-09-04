#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

const double PI = 3.14159265358979323846264;
int f[200001];

void swap(complex *a, complex *b){
    complex temp = *b;
    *b = *a;
    *a = temp;
}

void FFT(complex *vec, int n, int K){

    int j = 0;
    for(int i=1; i<n; i++){
        int index = n/2;
        while(!((j^=index)&index)) index /= 2;
        if(i<j) {
            swap(&vec[i],&vec[j]);

        }
    }

    for(int l=1; l<n; l*=2){
        double a = (K?-PI/l:PI/l);

        complex w = cos(a) + I*sin(a);

        for(int i=0; i<n; i += (l*2)){
            complex wp= 1.0 + 0.0*I;
            for(int k=0; k<l; k++){
                complex x = vec[i+k];
                complex y = vec[i+k+l]*wp;
                vec[i+k] = x+y;
                vec[i+k+l] = x-y;
                wp *= w;
            }
        }
    }

    if(K){
        for(int i=0; i<n; i++){
            vec[i] /= n;
        }
    }
    
}

complex *golf(int n, int N){
    complex *vec = (complex*)malloc(sizeof(complex)*n);
    vec[0] = 1.0 +0.0*I;
    for(int i=1; i<=N; i++){
        if(f[i]==0) vec[i] = 0.0+0.0*I;
        if(f[i]==1) vec[i] = 1.0+0.0*I;
    }
    for(int i=N+1; i<n; i++){
        vec[i] = 0.0 + 0.0*I;
    }
    FFT(vec,n,0);
    for(int i=0; i<n; i++){
        vec[i] *= vec[i];
    }
    FFT(vec,n,1);
    return vec;
}

int main(void){

    int N;
    scanf("%d", &N);
    memset(f, 0 ,sizeof(f));  
    for(int i=0; i<N; i++){
        int temp;
        scanf("%d", &temp);
        f[temp] = 1;
    }

    int size =1;
    while(size<=200000) size*=2;
    size *=2 ;
   
    complex *result = golf(size, 200000);

    int M;
    int ans=0;
    scanf("%d", &M);
    for(int i=0; i<M; i++){
        int temp;
        scanf("%d", &temp);
        if(round(creal(result[temp]))>0) {
            ans++;
        }
    }
    printf("%d\n", ans);
    

}