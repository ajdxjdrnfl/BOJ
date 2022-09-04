#include <stdio.h>

int parent[500001];
int rank[500001];

int checkP(int index){
    while(index!=parent[index]) index = parent[index];
    return index;
}

int main(void){
    int n,m,result=0;
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++){
        parent[i] = i;
    }
    for(int i=0; i<m; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        int pa = checkP(a);
        int pb = checkP(b);
        if(pa!=pb){
            if(rank[pa] < rank[pb]) parent[pa] = pb;
            else{
                parent[pb] = pa;
                if(rank[pa]==rank[pb]) rank[pa] = rank[pa] + 1;
            }             
        }
        else if(result==0) result = i+1;
    }
    printf("%d\n", result);
}