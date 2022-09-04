#include <stdio.h>
#include <stdlib.h>

int *arr;
int result[10];
void NandM(int N, int M, int height){

    if(M == height){
        for(int i=0; i<M; i++){
            printf("%d ", result[i]);
        }
        printf("\n");
        return ;
    }

    for(int i=0; i<N; i++){
        if(arr[i]==0) continue;

        result[height] = arr[i];
        arr[i] = 0;
        NandM(N,M, height+1);
        arr[i] = i+1;
    }
}
int main(void){
    int N, M;

    scanf("%d %d", &N, &M);
    arr = (int *)malloc(sizeof(int)*N);

    for(int i=0; i<N; i++){
        arr[i] = i+1;
    }
    NandM(N, M, 0);
}