#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int LENGTH = 12;
void heapsort(int *arr);
void max_heapify(int *arr, int index);
void make_heap(int *arr);
void swap(int *a, int *b);
void printArray(int *arr);
int main(void){

 int arr[LENGTH];
 int random = 0;
 srand(time(NULL));
 arr[0]=-1;
 for(int i=1; i<LENGTH; i++){
     // random값 
     random = rand()%20;
     arr[i]=random;
 }
printf("Original : ");
printArray(arr);   
heapsort(arr);


return 0;
}

void heapsort(int *arr){
    make_heap(arr);
    int first_len = LENGTH;
    int last = LENGTH-1;
    printf("Heapsort : ");
    for(int i=1; i<first_len; i++){
        printf("%d ", arr[1]);
        swap(&arr[1], &arr[last--]);
        LENGTH--;
        max_heapify(arr, 1);
    }
    printf("\n");
}

void max_heapify(int *arr, int index){
    int largest;
    if(index*2<LENGTH){
        
        int left = arr[index*2];
        int right =0;
        if(index*2+1<LENGTH){
        right = arr[index*2+1];
        }
        else{
        right = -1;
        }
        int mid = arr[index];

        largest = index;
        if(left>arr[largest]){
            largest=index*2;
        }
        if(right>arr[largest]){
            largest=index*2+1;
        }


        if(largest!=index){
           
            swap(&arr[index], &arr[largest]);
            max_heapify(arr, largest);
        }

    }
}

void make_heap(int *arr){
    if(LENGTH%2==1){
    for(int i=LENGTH/2; i>0; i--){
        max_heapify(arr, i);
    }
    }
    else{
        for(int i=LENGTH/2-1; i>0; i--){
    
        max_heapify(arr, i);
    }

    }
}

void swap(int *a, int *b){
    int temp;

    temp=*a;
    *a=*b;
    *b=temp;
}

void printArray(int *arr){
    for(int i=1; i<LENGTH; i++){
        printf("%d ", arr[i]);
        if(i==LENGTH-1) printf("\n");
    }
}