#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 1500000
int heap[1001];
int visited[1001];
int heap_size=0;
double edge[1001][1001];

typedef struct _POINT{
    long long x;
    long long y;
}POINT;

typedef struct _VERTEX{
    POINT loc;
    double key;
    int parent;
}VERTEX;


double sqrt(double n)
{
    double s=0;
    double t=0;
 
    s = n / 2;
    for (;s != t;)
    {
        t = s;
        s = ( (n / t) + t) / 2;
    }
    return s;
}

double squareSum(double a, double b){
    return a*a+b*b;
}
void swap(int a ,int b){
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}
void heapify(VERTEX *vertex, int index){

    int shortest = index;
    if(index*2<=heap_size && vertex[heap[index*2]].key < vertex[heap[shortest]].key) shortest = index*2;
    if(index*2+1<=heap_size && vertex[heap[index*2+1]].key < vertex[heap[shortest]].key) shortest = index*2+1;

    if(index!=shortest){
        swap(index, shortest);
        heapify(vertex, shortest);
    }
}

void makeHeap(VERTEX * vertex, int V){
    heap_size = V;
    for(int i=1; i<=heap_size; i++){
        heap[i] = i;
    }
    for(int i=heap_size/2; i>=1; i--){
        heapify(vertex, i);
    }
    
}

int extract_min(VERTEX *vertex){
    int temp = heap[1];
    heap[1] = heap[heap_size--];
    heapify(vertex, 1);
    return temp;
}

void update(VERTEX *vertex, int index){
    for(int i=index; i>=1; i/=2){
        heapify(vertex, i);
    }
}
void relax(VERTEX *vertex, int index, int V){
    
    for(int i=1; i<=V; i++){
        if(i==index) continue;
        if(edge[index][i] < vertex[i].key){
            vertex[i].key = edge[index][i];
            vertex[i].parent = i;
            for(int j=1; j<=heap_size; j++){
                if(heap[j] == i) update(vertex, j);
            }
        }
    }
}

double prim(VERTEX * vertex, int start, int V){
    vertex[start].key = 0;
    makeHeap(vertex, V);
    double result=0.00f;
    while(heap_size){
        int index = extract_min(vertex);
        result +=vertex[index].key;
        relax(vertex, index, V);     
    }
    return result;
}

int main(void){
    int N,M;
    scanf("%d %d", &N, &M);
    VERTEX *vertex = (VERTEX*)malloc(sizeof(VERTEX)*(N+1));
    for(int i=1; i<=N; i++){
        scanf("%lld %lld", &vertex[i].loc.x , &vertex[i].loc.y);
        vertex[i].key = INF;
        vertex[i].parent = i;
    }
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){

            double value = sqrt(squareSum(vertex[i].loc.x-vertex[j].loc.x, vertex[i].loc.y-vertex[j].loc.y)); 
            edge[i][j] = value;
            edge[j][i] = value; 
        }
    }
    for(int i=1; i<=M; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        edge[a][b] = 0;
        edge[b][a] = 0;
    }

    printf("%.2lf", prim(vertex, 1, N));
}