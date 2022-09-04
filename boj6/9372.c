#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parent[1001];
int rank[1001];

int checkP(int index){
    while(index!=parent[index]) index = parent[index];
    return index;
}
int main(void){
    int T;
    scanf("%d", &T);
    while(T--){
        int N,M,result=0;
        scanf("%d %d", &N, &M);
        memset(parent,0,sizeof(parent));
        memset(rank,0,sizeof(rank));

        for(int i=1; i<=N; i++){
            parent[i] = i;
            rank[i] = 1;
        }
        for(int i=0; i<M; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        int pa = checkP(a);
        int pb = checkP(b);
        if(pa==pb) continue;
        else{
            result++;
            if(rank[pa]<rank[pb]) parent[pa] = pb;
            else{
                parent[pb] = pa;
                if(rank[pa]==rank[pb]) rank[pa]++;
            }
        }
        
        }
        printf("%d\n", result);
    }
}