#include <stdio.h>
#include <stdlib.h>

void make_star(char **arr, int N, int boolean, int row, int col){
    
    if(boolean==-1){
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                arr[i+row][j+col] =' ';
            }

        }
        return;
    }
    else if(N!=3 && N%3==0){
        
        make_star(arr, N/3,1,row,col);
        make_star(arr, N/3,1,row,N/3+col);
        make_star(arr, N/3,1,row,(N/3)*2+col);
        make_star(arr, N/3,1,N/3+row,col);
        make_star(arr, N/3,-1,N/3+row,N/3+col);
        make_star(arr, N/3,1,N/3+row,(N/3)*2+col);
        make_star(arr, N/3,1,(N/3)*2+row,col);
        make_star(arr, N/3,1,(N/3)*2+row,N/3+col);
        make_star(arr, N/3,1,(N/3)*2+row,(N/3)*2+col);

        return;
    }
    else{
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            arr[i+row][j+col] ='*';
        }

    }
    arr[1+row][1+col] =' ';

    return;
    } 
}

void printMatrix(char **arr, int rowNum, int colNum){

    for(int i=0; i<rowNum; i++){
        for(int j=0; j<colNum; j++){
            printf("%c", arr[i][j]);

        }
        printf("\n");
    }
}
int main(void){

    int N;
    
    scanf("%d",&N);
    char **arr = (char **)malloc(sizeof(char *)*N);

    for(int i=0; i<N; i++){
        arr[i] = (char *)malloc(sizeof(char)*N);
    }

    make_star(arr, N,1,0,0);
    printMatrix(arr, N, N);
}