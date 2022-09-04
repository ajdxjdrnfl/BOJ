#include<stdio.h>
#include<stdlib.h>
/*
void quicksort(int *arr, int start, int last){
    if(start>=last) return;
   
    int pivot = arr[last];
    int j =last;
    int temp;
    for(int i=last-1; i>=start; i--){
        if(pivot<arr[i]) {
            temp = arr[--j];
            arr[j] = arr[i];
            arr[i] =  temp;
        }

    }
    temp = arr[j];
    arr[j] = pivot;
    arr[last] = temp;
    
    quicksort(arr,start, j-1);
    quicksort(arr, j+1, last);

}
*/
void Merge(int *a, int a_len, int *b, int b_len){

    int a_start=0;
    int b_start=0;

    int temp_a[a_len+1];
    int temp_b[b_len+1];
    temp_a[a_len]=1000001;
    temp_b[b_len]=1000001;

    
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

int main(void){
    int N;
    int *arr;

    scanf("%d", &N);
    arr = (int *)malloc(sizeof(int )*N);

    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }

    MergeSort(arr, N);
    for(int i=0; i<N; i++){

        printf("%d\n", arr[i]);
    }

}