#include <stdio.h>


int stack[10];
void NandM(int N, int M, int height){
    if(M==height+1){
        
        for(int i=stack[height-1]+1; i<=N-(M-(height+1)); i++ ){
            stack[height] = i;
            for(int i=0; i<M; i++){
                printf("%d ", stack[i]);
            }
            printf("\n");
        }
        return;
    }
    else if(height == 0){
        for(int i=1; i<=N-(M-1); i++){
            stack[height] = i;
            NandM(N, M, height+1);
        }
    }
    else{
        for(int i=stack[height-1]+1; i<=N-(M-(height+1));i++){
            stack[height] = i;
            NandM(N, M, height+1);
        
        }
    }
    
}


int main(void){

    int N,M;
    int *arr;
    scanf("%d %d", &N, &M);
    
    NandM(N,M,0);


}