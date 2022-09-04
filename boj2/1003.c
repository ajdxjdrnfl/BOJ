#include <stdio.h>
#include <stdlib.h>


int fibZero[41]={-1};
int fibOne[41]={-1};

int fibonacciZero(int n){
    if(fibZero[n]!=0) return fibZero[n];
    if(n==0){
        return 1;
    }

    else if(n==1){
        return 0;
    }
    else{
        int a = fibonacciZero(n-1);
        int b = fibonacciZero(n-2);
        fibZero[n] = a+b;
        
        return a+b;
    }
}

int fibonacciOne(int n){
    if(fibOne[n]!=0) return fibOne[n];

    if(n==0){
        return 0;
    }

    else if(n==1){
        return 1;
    }
    else{
        int a = fibonacciOne(n-1);
        int b = fibonacciOne(n-2);
        fibOne[n] = a+b;
     
        return a+b;
    }
}


int main(void){
    int N;
    int *arr;
  
    scanf("%d", &N);

    fibZero[0]=1;
    fibZero[1]=0;
    fibOne[0]=0;
    fibOne[1]=1;

    arr = (int*)malloc(sizeof(int)*N);
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }

    for(int i=0;i<N; i++){
        fibonacciZero(arr[i]);
        fibonacciOne(arr[i]);
    }
    
    for(int i=0; i<N; i++){
        printf("%d %d\n", fibZero[arr[i]],fibOne[arr[i]]);
    }

}