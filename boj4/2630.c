#include <stdio.h>
#include <stdlib.h>
#define BLACK 1
#define WHITE 0

void divide(int **arr, int col, int row, int size){
    if(size==1) {
        if(arr[col][row]==BLACK) printf("1");
        else printf("0");
        return;
    }
    
    int temp;
    int omit=0;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(i==0 && j==0) temp = arr[col+i][row+j];
            else if(temp!=arr[col+i][row+j]) {
                omit=1;
                break;
            }
        }
        if(omit==1) break;
        if(i==size-1){
            if(arr[col][row]==BLACK) printf("1");
            else printf("0");
            return;
        }
    }
    printf("(");
    divide(arr, col, row, size/2);
    divide(arr, col, row+size/2, size/2);
    divide(arr, col+size/2, row, size/2);
    divide(arr, col+size/2, row+size/2, size/2);
    printf(")");
}
int main(void){
    int N;
    
    scanf("%d", &N);
   
    int **arr;
    char temp[N][N+1];
    arr =(int**)malloc(sizeof(int*)*N);
    for(int i=0; i<N; i++){
        arr[i] = (int*)malloc(sizeof(int)*N);
    }
    for(int i=0; i<N; i++){
        scanf("%s", temp[i]);
        for(int j=0; j<N; j++){
            arr[i][j] = temp[i][j] - '0';
        }
    }
    
    divide(arr,0,0,N);
    printf("\n");
}