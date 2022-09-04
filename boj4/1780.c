#include <stdio.h>
#include <stdlib.h>
#define LEFT -1
#define MID 0
#define RIGTH 1

int left=0, mid=0, right=0;
void divide(int **arr, int row, int col, int size){
    
    int temp;
    int omit=0;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(i==0 && j==0) temp = arr[row+i][col+j];
            else if(temp != arr[row+i][col+j]) {
                omit=1;
                break;
            }
        }
        if(omit==1) break;
        if(i==size-1){
            if(temp==LEFT) left++;
            else if(temp==MID) mid++;
            else if(temp==RIGTH) right++;
            return;
        }
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            divide(arr, row+(size/3)*i,col+(size/3)*j, size/3);
        }
    }
}
int main(void){
    int N;
    scanf("%d", &N);
    int **arr;
    
    arr =(int**)malloc(sizeof(int*)*N);
    for(int i=0; i<N; i++){
        arr[i] = (int*)malloc(sizeof(int)*N);
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            scanf("%d", &arr[i][j]);
        }
    }
    divide(arr, 0, 0, N);
    printf("%d\n", left);
    printf("%d\n", mid);
    printf("%d\n", right);
}