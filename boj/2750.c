#include<stdio.h>
#include<stdlib.h>

void swap(int *arr, int j, int i){
    int temp = arr[j];
    arr[j]= arr[i];
    arr[i] = temp;
}

void insertSort(int *arr, int N){

    for(int i=1; i<N; i++){
        int smallest;
        int count = i;
        for(int j=i-1; j>=0; j--){
            if(arr[j]>arr[count]) {
                swap(arr, j, count);
                count=j;}
            else  {
                break;
            }

        }


    }


}

int main (void){

    int *arr;
    int N;
    scanf("%d", &N);
    arr = (int *)malloc(sizeof(int)*N);
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }

    insertSort(arr, N);
    for(int i=0; i<N; i++){
        printf("%d\n", arr[i]);
    }
}