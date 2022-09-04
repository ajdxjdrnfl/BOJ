#include <stdio.h>

int stack[10];
void NandM(int N, int M, int height){
    if(M == height){
        for(int i=0; i<M; i++){
            printf("%d ", stack[i]);
        }
        printf("\n");
        return;
    }


    if(height==0){
        for(int i=1; i<=N; i++){
        stack[height] = i;
        NandM(N, M, height+1);
    }
    }
    else{
    for(int i=stack[height-1]; i<=N; i++){
        stack[height] = i;
        NandM(N, M, height+1);
    }
    }
}
int main(void){

    int N,M; 
    scanf("%d %d", &N, &M);
    NandM(N, M, 0);
}