#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int smallest=10000000;

int *stack;
int *player;
int playerSum(int **stats, int *team, int N){
    int result=0;
    for(int i=0; i<N; i++ ){
        for(int j=0; j<N; j++){
            result+=stats[team[i]][team[j]];
        }

    }

    return result;
}

void startLink(int **stats, int N, int height){
    if(N/2== height){
        int start[N];
        int Link[N];
        int startIndex=0, linkIndex=0;
        int startSum=0, linkSum=0;
        for(int i=0; i<N; i++){
            if(player[i]==0) start[startIndex++] = i;
            else Link[linkIndex++] =i;
        }
        startSum = playerSum(stats, start, startIndex);
        linkSum = playerSum(stats, Link, linkIndex);
        
        if(smallest>abs(startSum - linkSum)) smallest = abs(startSum - linkSum);
        return;
    }

    if(height == 0){
        for(int i=0; i<=N/2; i++){
            if(player[i]==0) continue;
        else{
            player[i]=0;
            stack[height]=i;
            startLink(stats, N, height+1);
            player[i]=1;
        }
        }
    }
    else{
    for(int i=stack[height-1]+1; i<=N/2+height; i++){
        if(player[i]==0) continue;
        else{
            player[i]=0;
            stack[height]=i;
            startLink(stats, N, height+1);
            player[i]=1;
        }
    }
    }


}
int main(void){

    int N;
    int **stats;
    scanf("%d", &N);
    player = (int*)malloc(sizeof(int)*N);
    stack = (int*)malloc(sizeof(int)*N);
    stats = (int **)malloc(sizeof(int*)*N);
    for(int i=0; i<N; i++){
        stats[i] = (int *)malloc(sizeof(int)*N);
        stack[i] = 0;
    }

    for(int i=0; i<N; i++){
        player[i] =1;
        for(int j=0; j<N; j++){
            scanf("%d", &stats[i][j]);

        }
    }

    startLink(stats,N,0);
    printf("%d\n", smallest);

}