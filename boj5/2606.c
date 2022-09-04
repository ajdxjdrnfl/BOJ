#include <stdio.h>
#include <string.h>

int comp[101][101];
int visited[101]={0,};
int dfs(int num , int N){
    int ans=1;
    visited[num]=1;
    for(int i=1; i<=N; i++){
        if(visited[i]==0 && comp[num][i]==1){
            
            ans+=dfs(i, N);
        }
    }
    return ans;
}
int main(void){

    int N,M;
    scanf("%d", &N);
    scanf("%d", &M);
    memset(comp, 0, sizeof(comp));
    for(int i=0; i<M; i++){
        int a,b;
        scanf("%d %d", &a,&b);
        comp[a][b] = 1;
        comp[b][a] = 1;
    }

    int ans = dfs(1,N);
    printf("%d\n", ans-1);
}