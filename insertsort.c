#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define LENGTH 12

void InsertSort(int *arr);
void printArray(int *arr);

int main(void){

    int arr[LENGTH];
    int random=0;
    srand(time(NULL));

    for(int i=0; i<LENGTH; i++ ){
        random = rand()%20;
        arr[i]=random;
    }
    printf("Original : ");
    printArray(arr);
    InsertSort(arr);
    printf("Insertion Sort : ");
    printArray(arr);
    
    return 0;
    
    
    
}

void InsertSort(int *arr){

    int temp=0;
    for(int i=1; i<LENGTH; i++){
        temp = arr[i];
        for(int j=i-1; j>=0; j--){
            if(temp>arr[j]){
                arr[j+1]=temp;
                break;
            }
            else{
                arr[j+1]=arr[j];
            }
            if(j==0){
                arr[j]=temp;
            }
        }
    }
}

void printArray(int *arr){

    for(int i=0; i<LENGTH; i++){
        printf("%d ", arr[i]);
        if(i==LENGTH-1){
            printf("\n");
        }
    }
}