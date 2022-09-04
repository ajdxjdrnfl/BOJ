#include <stdio.h>
#include <stdlib.h>

int **result;

void triangle(int **arr, int N){

    for(int i=0; i<N; i++){
        for(int j=0; j<i+1; j++){
            if(i==0 && j==0){
                result[0][0] =  arr[0][0];
            }
            else{
                if(j==0){
                    result[i][j] = arr[i][j] + result[i-1][j];
                }
                else if(j==i){
                    result[i][j] = arr[i][j] + result[i-1][j-1];
                }
                else{
                    if(result[i-1][j]<result[i-1][j-1]) result[i][j] = arr[i][j] + result[i-1][j-1];
                    else result[i][j] = arr[i][j] + result[i-1][j];
                }
            }
        }
    }

}

int main(void){
    int N;
    int **arr;
    int largest;
    scanf("%d", &N);

    arr = (int **)malloc(sizeof(int*)*N);
    result = (int **)malloc(sizeof(int*)*N);
    for(int i=0; i<N; i++){
        arr[i] = (int *)malloc(sizeof(int)*(i+1));
        for(int j=0; j<i+1; j++){
            scanf("%d", &arr[i][j]);
        }
        result[i] = (int *)malloc(sizeof(int)*(i+1));
    }
    
    triangle(arr, N);

    for(int i=0; i<N; i++){
        if(i==0) largest = result[N-1][i];
        else if(largest < result[N-1][i]) largest = result[N-1][i];
    }

    printf("%d\n", largest);

}