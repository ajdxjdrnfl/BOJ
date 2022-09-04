#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int comp(const void *a, const void *b){
    int pa = *(int*)a;
    int pb = *(int*)b;

    if(pa<pb) return -1;
    else if(pa>pb) return 1;
    return 0;
}
int apart[25][25];
int visited[25][25];

int danji(int col, int row, int N){

    int ans = 1;
    visited[col][row]=1;
    if(row+1<N && apart[col][row+1]==1 && visited[col][row+1] ==0 ) ans+=danji(col, row+1, N);
    if(col+1<N && apart[col+1][row]==1 && visited[col+1][row]==0) ans+=danji(col+1, row, N);
    if(row-1>=0 && apart[col][row-1] && visited[col][row-1]==0) ans+=danji(col, row-1, N);
    if(col-1>=0 && apart[col-1][row] && visited[col-1][row]==0) ans+=danji(col-1, row, N);

    return ans; 
}
int main(void){
    int N;
    int cnt=0;
    int ans[625];
    scanf("%d", &N);
    memset(apart, 0, sizeof(apart));
    memset(visited, 0, sizeof(visited));
    for(int i=0; i<N; i++){
        char s[10];
        scanf("%s", s);
        for(int j=0; j<N; j++){
            apart[i][j]=s[j]-'0';
        }
    }
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(apart[i][j]==1 && visited[i][j]==0) ans[cnt++] = danji(i, j, N);
        }
            
    }
        
    
    printf("%d\n", cnt);
    qsort(ans, cnt, sizeof(int), comp);
    for(int i=0; i<cnt; i++){
        printf("%d\n", ans[i]);
    }

}