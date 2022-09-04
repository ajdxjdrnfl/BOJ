#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define LENGTH 12

void quicksort(int *arr, int start, int last);
void printArray(int *arr);
int main(void){
    int arr[LENGTH];
  
    srand(time(NULL));
    arr[0] = -1;
    for(int i=1; i<LENGTH; i++){

        arr[i]=rand()%20;

    }
    printf("Original : ");
    printArray(arr);
    
    quicksort(arr, 1, LENGTH-1);
    printf("QUICK SORT : ");
    printArray(arr);

}

void quicksort(int *arr, int start, int last){
    
    if(start>=last) {
        return ;
    }
    
    int pivot = arr[last];
    int first = start-1;
    int temp =0;
    printf("start  : %d, last : %d\n", start, last);
    for(int i=start; i<last; i++){
        if(arr[i]<pivot){
            temp=arr[++first];
            arr[first]=arr[i];
            arr[i]=temp;
        }
    }
    temp = arr[++first];
    arr[first] = arr[last];
    arr[last] = temp;
    
    quicksort(arr, start, first-1);
    quicksort(arr, first+1, last);
}

void printArray(int *arr){
    for(int i=1; i<LENGTH; i++){
        printf("%d ", arr[i]);
        if(i==LENGTH-1) printf("\n");
    }
     
}