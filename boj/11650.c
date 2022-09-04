#include <stdio.h>
#include <stdlib.h>

void merge(int a[][2], int a_len, int b[][2], int b_len){
    
    int a_start=0, b_start=0;
    int temp_a[a_len+1][2];
    int temp_b[b_len+1][2];
    temp_a[a_len][1] = 100001;
    temp_b[b_len][1] = 100001;

    for(int i=0; i<a_len; i++){
        temp_a[i][0]=a[i][0];
        temp_a[i][1]=a[i][1];
    }
    for(int i=0; i<b_len; i++){
        temp_b[i][0]=b[i][0];
        temp_b[i][1]=b[i][1];
    }
    for(int i=0; i<a_len+b_len; i++){
        if(temp_a[a_start][1]<temp_b[b_start][1]){
            a[i][0] = temp_a[a_start][0];
            a[i][1] = temp_a[a_start++][1];
        }
        else if(temp_a[a_start][1] == temp_b[b_start][1]){
            if(temp_a[a_start][0]<temp_b[b_start][0]){
                a[i][0] = temp_a[a_start][0];
                a[i][1] = temp_a[a_start++][1];
            }
            else{
                a[i][0] = temp_b[b_start][0];
                a[i][1] = temp_b[b_start++][1];
            }
        }
        else{
            a[i][0] = temp_b[b_start][0];
            a[i][1] = temp_b[b_start++][1];
        }
    }

}


void mergeSort(int arr[][2], int N){
    if(N==1) return;
    if(N%2==0){
    mergeSort(&arr[0], N/2);
    mergeSort(&arr[N/2], N/2);
    merge(&arr[0], N/2, &arr[N/2], N/2);
    }

    else{
        mergeSort(&arr[0],N/2);
        mergeSort(&arr[N/2], N/2+1);
        merge(&arr[0], N/2, &arr[N/2], N/2+1);
    }
    
}


int main(void){
    int N;

    scanf("%d", &N);
    int arr[N][2];

    for(int i=0; i<N; i++){
        scanf("%d %d",&arr[i][0], &arr[i][1]);
    }

    mergeSort(arr, N);
    for(int i=0; i<N; i++){
        printf("%d %d\n", arr[i][0], arr[i][1]);
    }
}