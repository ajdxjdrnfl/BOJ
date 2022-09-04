#include <stdio.h>
#include <stdlib.h>

int parent[10001];
int rank[10001];
typedef struct _EDGE{
    int u;
    int v;
    int weight;
}EDGE;

int comp(const void*a, const void*b){
    EDGE pa = *(EDGE*)a;
    EDGE pb = *(EDGE*)b;
    if(pa.weight<pb.weight) return -1;
    else if(pa.weight>pb.weight) return 1;
    return 0;
}

int checkP(int index){
    while(index!=parent[index]) index = parent[index];
    return index;
}

int main(void){
    int V,E, result=0;
    scanf("%d %d", &V, &E);
    EDGE * edge = (EDGE*)malloc(sizeof(EDGE)*(E));
    for(int i=1; i<=V; i++){
        parent[i] = i;
        rank[i] = 1;
    }
    for(int i=0; i<E; i++){
        int a,b,c;
        scanf("%d %d %d", &a, &b, &c);
        edge[i].u = a;
        edge[i].v = b;
        edge[i].weight = c;
        
    }
    qsort(edge, E, sizeof(EDGE), comp);

    for(int i=0; i<E; i++){
        int a = edge[i].u, b = edge[i].v;
        int pa = checkP(a);
        int pb = checkP(b);

        if(pa==pb) continue;
        else{
            result += edge[i].weight;
            if(rank[pa] < rank[pb]) parent[pa] = pb;
            else{
                parent[pb] = pa;
                if(rank[pa]==rank[pb]) rank[pa]++;
            }
        }
    }
    printf("%d\n", result);

}