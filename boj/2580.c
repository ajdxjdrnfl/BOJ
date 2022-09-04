#include <stdio.h>
#include <stdlib.h>

int rowStack[81];
int columnStack[81];
int stack[82]={0,};
int zeroNum=0;
int findUnable(int **arr, int row, int column, int value){
    for(int i=0; i<9; i++){
        if(arr[row][i]==value) return -1;
        if(arr[i][column]==value) return -1;
        if(arr[row][i]==0){
           if(stack[row*9+i]==value) return -1;
        }
        if(arr[i][column]==0){
            if(stack[i*9+column]==value) return -1;
        }
    }
    int rowEff = row/3;
    int columnEff =  column/3;

    for(int i=0; i<3; i++){
       if( arr[rowEff*3+i][columnEff*3] == value ) return -1;
       if( arr[rowEff*3+i][columnEff*3+1] == value ) return -1;
       if( arr[rowEff*3+i][columnEff*3+2] == value ) return -1;

       if(arr[rowEff*3+i][columnEff*3]==0){
           if(stack[(rowEff*3+i)*9+columnEff*3]== value) return -1;
       }
       if(arr[rowEff*3+i][columnEff*3+1]==0){
           if(stack[(rowEff*3+i)*9+columnEff*3+1]== value) return -1;
       }
       if(arr[rowEff*3+i][columnEff*3+2]==0){
           if(stack[(rowEff*3+i)*9+columnEff*3+2]== value) return -1;
       }
    }
    
    return 1;
}

int sudoku(int **arr, int row, int column, int height){
    
    if(zeroNum == height){
        printf("끝\n");
        return 1;
    }

    for(int i=1; i<=9; i++){
        
        if(findUnable(arr, row, column, i) != -1){
        stack[row*9+column] = i;
        if(sudoku(arr,rowStack[height+1], columnStack[height+1] ,height+1)==1) return 1;
        stack[row*9+column] = 0;
        }
    }

    return -1;
}

int main(void){

    int **arr;
    
    arr = (int **)malloc(sizeof(int*)*9);
    for(int i=0; i<9; i++){
        arr[i] = (int *)malloc(sizeof(int)*9);
    }

    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            scanf("%d", &arr[i][j]);
            if(arr[i][j] == 0) {
                rowStack[zeroNum]=i;
                columnStack[zeroNum++] =j;
            }
                
        }
    }
    if(zeroNum!=0){
    sudoku(arr, rowStack[0], columnStack[0], 0);
    }
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(arr[i][j] == 0) printf("%d ",stack[i*9+j]);
            else printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}