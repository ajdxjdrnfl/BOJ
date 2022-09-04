#include <stdio.h>
#include <string.h>

int arr[1001][1001];
int que[1001];
int start=0, end=0;

int check1[1001];
int check2[1001];
void dfs(int num, int N){
    check1[num]=1;
    printf("%d ", num);
    for(int i=1; i<=N; i++){
        if(arr[num][i]==1 && check1[i]==0){
            dfs(i, N);
        }

    }
}

void bfs(int num, int N){
    
    printf("%d ", num);
    for(int i=1; i<=N; i++){
        if(arr[num][i]==1 && check2[i]==0){
            check2[i]=1;
            que[end++]=i;
        }
    }
}
int main(void){
    int N, M, V; 
    scanf("%d %d %d", &N, &M, &V);
    memset(arr, 0, sizeof(arr));
    memset(check1, 0, sizeof(check1));
    memset(check2, 0, sizeof(check2));
    for(int i=0; i<M; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        arr[a][b]=1;
        arr[b][a]=1;
    }
    
    dfs(V, N);
    printf("\n");
    check2[V]=1;
    que[end++]=V;
    while(start<end){
        bfs(que[start++],N);
    }
    printf("\n");
}
    
    
