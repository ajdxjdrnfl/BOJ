#include <stdio.h>
#include <stdlib.h>

int BinarySearch(int *arr, int N,int object){
    int low=0, high=N-1;
    int mid, temp;
    while(low<=high){
        mid = (low+high)/2;
        temp = arr[mid];

        if(temp == object) return mid;
        else if(temp > object){
            high = mid-1;
        }
        else{
            low = mid+1;
        }
        
    }
    
    return -1;

}

void merge(int *a, int a_len, int*b, int b_len){

    int a_start=0, b_start=0;

    int temp_a[a_len+1], temp_b[b_len+1];

    temp_a[a_len] = 1000000001;
    temp_b[b_len] = 1000000001;

    for(int i=0; i<a_len; i++){
        temp_a[i] = a[i];
        
    }
  
    for(int i=0;i<b_len; i++){
        temp_b[i] = b[i];
      
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

void mergeSort(int *arr, int N){

    if(N==1) return;

    if(N%2==0){
        mergeSort(&arr[0], N/2);
        mergeSort(&arr[N/2], N/2);
        merge(&arr[0], N/2, &arr[N/2], N/2);
    }
    else{
        mergeSort(&arr[0], N/2);
        mergeSort(&arr[N/2], N/2+1);
        merge(&arr[0], N/2, &arr[N/2], N/2+1);
    }
}


void findPosition(int *coord, int size,int *arr, int N){

    for(int i=0; i<N; i++){

        int position = BinarySearch(coord, size, arr[i]);
        printf("%d ",position);
    }
    
}

int main(void)
{
    int *coord;
    int size=0;
    int save;
    int N;
    int *arr, *brr;
    scanf("%d", &N);
    arr =(int *)malloc(sizeof(int)*N);
    brr =(int *)malloc(sizeof(int)*N);
    coord = (int *)malloc(sizeof(int)*N);
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }
    for(int i=0; i<N; i++){
        brr[i] = arr[i];
        
    }
    
    mergeSort(arr, N);
    

    for(int i=0; i<N; i++){
        if(i==0) {
            save = arr[i]; 
            coord[size++] = arr[i];
        }
        else{
            if(save==arr[i]) continue;
            else{
                coord[size++] = arr[i];
                save = arr[i];
            }
        }
        
    }
   
    findPosition(coord,size, brr, N); 

}