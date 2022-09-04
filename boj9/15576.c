#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <string.h>

int A[300001], B[300001];
const double PI = 3.14159265358979323846264;
int size_A=0, size_B=0;
int size=1;
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

complex * bigNum(int n){
   
    while(size<=n) size*=2;
    size *=2;

    complex *x = (complex*)malloc(sizeof(complex)*size);
    complex *y = (complex*)malloc(sizeof(complex)*size);

    memset(x, 0 , sizeof(x));
    memset(y, 0, sizeof(y));
    for(int i=0; i<size_A; i++){
        x[i] = (double)A[i] + 0.0*I;
    }
    for(int i=0; i<size_B; i++){
        y[i] = (double)B[i] + 0.0*I;
    }

    FFT(x, size, 0);
    FFT(y, size, 0);

    complex * res = (complex*)malloc(sizeof(complex)*size);
    memset(res, 0 ,sizeof(res));
    for(int i=0; i<size; i++){
        res[i] = x[i]*y[i];
    }

    FFT(res, size, 1);
    return res;
}
int main(void){

    char temp_A[300010], temp_B[300010];
    scanf("%s", temp_A);
    scanf("%s", temp_B);
    
    for(int i=0; temp_A[i]; i++){
        A[i] = temp_A[i]-'0';
        size_A++;
    }
    for(int i=0; temp_B[i]; i++){
        B[i] = temp_B[i]-'0';
        size_B++;
    }
    complex * res = bigNum(300000);
    int result[size];
  
    memset(result, 0, sizeof(result));
    
    int carry = 0;
    for(int i=size_A+size_B-2; i>=0; i--){
        int temp = (int)round(creal(res[i]))+carry;
        if(i!=0) result[i] += (temp%10);
        else result[i] += temp;
        carry = temp/10;
        
    }
    for(int i=0; i<=size_A+size_B-2; i++){
        printf("%d", result[i]);
    }
    printf("\n");
}