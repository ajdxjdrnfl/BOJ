#include <stdio.h>
#include <stdlib.h>


char white[8][8], black[8][8];
int checkW(char **arr, int startRow, int startCol){

    int num=0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(arr[startRow+i][startCol+j]!=white[i][j]) num++;
        }
    }
    return num;
}

int checkB(char **arr, int startRow, int startCol){
    int num=0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(arr[startRow+i][startCol+j]!=black[i][j]) num++;
        }
    }
    return num;
}

int check(char **arr, int rowNum, int colNum){
    int whiteNum, blackNum =0;
    int smallest = 65;
    for(int i=0; i<rowNum-7; i++){
        for(int j=0; j<colNum-7; j++){
            whiteNum = checkW(arr, i, j);
            blackNum = checkB(arr, i, j);
            if(smallest>whiteNum) smallest = whiteNum;
            if(smallest>blackNum) smallest = blackNum;    
        }
        
    }

    return smallest;

}

int main(void){


    int M,N;
    char **arr;
    
    scanf("%d %d", &M, &N);
    

    arr = (char **)malloc(sizeof(char *)*M);
    
    for(int i=0; i<M; i++){
        arr[i] = (char *)malloc(sizeof(char)*(N+1));
    }

    for(int i=0; i<M; i++){        
            scanf("%s", arr[i]);
        
    }
    
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(j%2==1){
                if(i%2==1){
                    white[i][j] = 'W';
                    black[i][j] = 'B';
                }
                else{
                    white[i][j] = 'B';
                    black[i][j] = 'W';

                }

            }

            else{
                if(i%2==1){
                    white[i][j] = 'B';
                    black[i][j] = 'W';
                }
                else{
                    white[i][j] = 'W';
                    black[i][j] = 'B';
                }
            }
            
        }
    }
    
    printf("%d", check(arr, M, N));

}