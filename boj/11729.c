#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int *arr;
int result;
void hanoi(int num, int object){

    if(num==1){
    
        printf("%d %d\n",arr[num-1], object);
        arr[num-1] = object;
        result++;
        return;
    }

    else{
    int nextObject;
    for(int i=1; i<=3; i++){
        if(i!=object && i!=arr[num-2]) nextObject = i;
    }
    
    hanoi(num-1, nextObject);

    printf("%d %d\n", arr[num-1], object);
    result++;
    arr[num-1] = object;
    hanoi(num-1, object);

    }
}
int intPow(int n, int m){
    if(m==0) return 1;
    return n*intPow(n,m-1);
}
int main(void){
    int N;
    scanf("%d", &N);
    arr = malloc(sizeof(int)*N);
    for(int i=0; i<N; i++){
        arr[i] = 1;
    }
    result = 0;
    printf("%d\n", intPow(2,N)-1);
    hanoi(N, 3);
    
}

