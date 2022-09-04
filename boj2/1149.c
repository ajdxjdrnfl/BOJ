#include <stdio.h>
#include <stdlib.h>

int *red;
int *green;
int *blue;
int main(void){
    int N;
    int **arr;
    scanf("%d", &N);

    arr = (int**)malloc(sizeof(int*)*N);
    red = (int *)malloc(sizeof(int)*N);
    green = (int *)malloc(sizeof(int)*N);
    blue = (int *)malloc(sizeof(int)*N);
    for(int i=0; i<N; i++){
        arr[i] = (int *)malloc(sizeof(int)*3);
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<3; j++){
            scanf("%d", &arr[i][j]);
        }
    }

    red[0] = arr[0][0];
    green[0] = arr[0][1];
    blue[0] = arr[0][2];
    
    for(int i=1; i<N; i++){
        if(red[i-1]<green[i-1]) blue[i] = red[i-1] + arr[i][2];
        else blue[i] = green[i-1] + arr[i][2];

        if(red[i-1]<blue[i-1]) green[i] = red[i-1] + arr[i][1];
        else green[i] = blue[i-1] + arr[i][1];

        if(green[i-1]<blue[i-1]) red[i] = green[i-1] + arr[i][0];
        else red[i] = blue[i-1] + arr[i][0];

    }
    int smallest = red[N-1];
   if(smallest>green[N-1]) smallest = green[N-1];
   if(smallest>blue[N-1]) smallest = blue[N-1];
    
   printf("%d\n", smallest);
    
}