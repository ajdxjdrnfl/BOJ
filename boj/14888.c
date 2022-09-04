#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int arith[4]={0,};
int largest=-1000000001, smallest=1000000001;
int arithNum=0;
int stack[100];

int add(int a, int b){
    return a+b;
}

int subtract(int a, int b){
    return a-b;

}

int divide(int a, int b){
    if(a<0)return -abs(a)/b;
    else return a/b;
}

int multiply(int a, int b){
    return a*b;
}

int arithApply(int a, int b, int index){
    switch (index)
    {
    case 0:
        return add(a,b);
        break;
    case 1:
        return subtract(a,b);
        break;
    
    case 2:
        return multiply(a,b);
        break;

    case 3:
        return divide(a,b);
        break;
    default:
        break;
    }
}


void arithInsert(int *arr, int N,int height){

    if(arithNum == height){
        int result=0;
        int temp=arr[0];
        for(int i=1; i<N; i++){
            temp = arithApply(temp, arr[i], stack[i-1]);
        }
        result = temp;
        if(smallest>result) smallest = result;
        if(largest<result) largest = result;
        return;
    }

    for(int i=0; i<4; i++){
        if(arith[i]!=0){
        stack[height] = i;
        arith[i]--;
        arithInsert(arr, N, height+1);
        arith[i]++;
        }
    }


}
int main(void){

    int N;
    int *arr;
    

    scanf("%d", &N);
    arr = (int *)malloc(sizeof(int)*N);
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }

    for(int i=0; i<4; i++){
        scanf("%d", &arith[i]);
        arithNum+=arith[i];
    }


    arithInsert(arr,N,0);
    printf("%d\n", largest);
    printf("%d\n", smallest);


}