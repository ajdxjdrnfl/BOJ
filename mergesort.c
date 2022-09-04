#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define LENGTH 12

void MergeSort(int *arr, int len);
void Merge(int *a, int a_len, int *b, int b_len);
void printArray(int *arr);

int main(void){
    int arr[LENGTH];
    int random=0;
    srand(time(NULL));
    
    for(int i=0; i<LENGTH; i++){

        random = rand()%20;
        arr[i]=random;
    }

    printf("Original : ");
    printArray(arr);
    MergeSort(arr, LENGTH);
    printf("Mergesort : ");
    printArray(arr);

    return 0;
}

void MergeSort(int *arr, int len){

    if(len==1) return;

    if(len%2==0){
    MergeSort(arr, len/2);
    MergeSort(arr+len/2, len/2);
    Merge(arr, len/2, arr+len/2, len/2);
    }

    else{

        MergeSort(arr, len/2);
        MergeSort(arr+len/2, len/2+1);
        Merge(arr, len/2, arr+len/2, len/2+1);
    }
}

void Merge(int *a, int a_len, int *b, int b_len){

    int a_start=0;
    int b_start=0;

    int temp_a[a_len+1];
    int temp_b[b_len+1];
    
    temp_a[a_len]=21;
    temp_b[b_len]=21;

    
    for(int i=0; i<a_len; i++){
        temp_a[i]=a[i];
    }
    for(int i=0; i<b_len; i++){
        temp_b[i]=b[i];
    }

    for(int i=0; i<a_len+b_len; i++){
        if(temp_a[a_start]<temp_b[b_start]){
            a[i]=temp_a[a_start++];
        }
        else{
            a[i]=temp_b[b_start++];
        }
    }


}

void printArray(int *arr){
    for(int i=0; i<LENGTH; i++){
        printf("%d ", arr[i]);
        if(i==LENGTH-1) printf("\n");
    }
}a