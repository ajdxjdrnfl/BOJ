#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int stack[15];
int result=0;

int findUnable(int row, int column, int N){
   for(int i=0; i<row; i++){
        if(stack[i] == column) return -1;
        if(abs(row-i)== abs(column-stack[i])) return -1;
   }

   return 1;
}


void N_Queen(int row, int N){
    int column;
    if(row == N){
        
        result++;
        return;
    }
    
    for(int i=0; i<N; i++){
        
        if(findUnable(row, i, N)!=-1){
        
        stack[row] = i;
        N_Queen(row+1, N);
        }

       else{
           continue;}
        
        
    }
    return;
}


int main(void){
    
    int N;
    scanf("%d", &N);
    
    N_Queen(0,N);
    printf("%d", result);
}