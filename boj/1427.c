#include <stdio.h>

void insertSort(int *arr, int N){

    for(int i=1; i<N; i++){
        int temp = arr[i];
        for(int j=i-1; j>=0; j--){
            if(temp<arr[j]){
                arr[j+1] = temp;
                break;
            }
            else{
                arr[j+1] = arr[j];
            }
            if(j==0){
                arr[j] = temp;
            }

        }

    }
}

int main(void){
    int num;
    int N=0, arr[10];
    scanf("%d", &num);
    
    for(int i=num; i>0; i=i/10){
        arr[N] = i%10;
        N++;    
    }
    
    insertSort(arr, N);
    for(int i=0; i<N; i++){
        printf("%d",arr[i]);
    }
    printf("\n");
}