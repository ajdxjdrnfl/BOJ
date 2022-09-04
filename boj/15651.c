#include <stdio.h>

int stack[10];
void NandM(int N, int M, int height){
    if(height == M){
        for(int i=0; i<M; i++){
        printf("%d ",stack[i] );
        }
        printf("\n");
        return ;
    }

    for(int i=1; i<=N; i++){
        stack[height] = i;
        NandM(N, M, height+1);
    }
}
int main(void){

    int N,M;
    scanf("%d %d", &N, &M);

    NandM(N, M, 0);
}