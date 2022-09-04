#include <stdio.h>
#include <stdlib.h>

typedef struct _POINT{
    int x;
    int y;
    int z;
    int index;
}POINT;

typedef struct _EDGE{
    int u;
    int v;
    int weight;
}EDGE;

POINT point[100001];
EDGE edge[300000];
int parent[100001];
int rank[100001];
int min(int a, int b){
    return a>b?b:a;
}

int comX(const void*a, const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;

    if(pa.x<pb.x) return -1;
    else if(pa.x>pb.x) return 1;
    return 0;
}

int comY(const void*a, const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;

    if(pa.y<pb.y) return -1;
    else if(pa.y>pb.y) return 1;
    return 0;
}

int comZ(const void*a, const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;

    if(pa.z<pb.z) return -1;
    else if(pa.z>pb.z) return 1;
    return 0;
}

int comE(const void*a, const void*b){
    EDGE pa = *(EDGE*)a;
    EDGE pb = *(EDGE*)b;

    if(pa.weight < pb.weight) return -1;
    else if(pa.weight > pb.weight) return 1;
    return 0;
}

int checkP(int index){
    while(index!=parent[index]) index = parent[index];
    return index;
}
int main(void){
    int N;
    int size=0, result=0;
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%d %d %d", &point[i].x, &point[i].y, &point[i].z);
        point[i].index = i;
        parent[i] = i;
        rank[i] = 1;
    }
    qsort(point , N, sizeof(POINT), comX);
    for(int i=0; i<N-1; i++){
        edge[size].u = point[i].index;
        edge[size].v = point[i+1].index;
        edge[size++].weight = point[i+1].x - point[i].x;
    }
    qsort(point , N, sizeof(POINT), comY);
    for(int i=0; i<N-1; i++){
        edge[size].u = point[i].index;
        edge[size].v = point[i+1].index;
        edge[size++].weight = point[i+1].y - point[i].y;
    }
    qsort(point , N, sizeof(POINT), comZ);
    for(int i=0; i<N-1; i++){
        edge[size].u = point[i].index;
        edge[size].v = point[i+1].index;
        edge[size++].weight = point[i+1].z - point[i].z;
    }
    qsort(edge, size, sizeof(EDGE), comE);
    for(int i=0; i<size; i++){
        int pa = checkP(edge[i].u);
        int pb = checkP(edge[i].v);
        if(pa==pb) continue;
        else{
            result+=edge[i].weight;
            if(rank[pa] < rank[pb]) parent[pa] = pb;
            else{
                parent[pb] = pa;
                if(rank[pa]==rank[pb]) rank[pa]++;
            }
        }
    }
    printf("%d\n", result);

}