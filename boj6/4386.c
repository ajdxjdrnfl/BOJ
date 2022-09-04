#include <stdio.h>
#include <stdlib.h>

#define INF 2000001
int heap[101];
int heap_size=0;

typedef struct _POINT{
    float x;
    float y;
}POINT;

typedef struct _VERTEX{
    POINT loc;
    float key;
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

float squareSum(float a, float b){
    return a*a+b*b;
}

void update(VERTEX * vertex, int index){
    for(int i=index; i>=1; i/=2){
        heapify(vertex, i);
    }
}

void relax(VERTEX *vertex, int index, int V){
    float x = vertex[index].loc.x;
    float y = vertex[index].loc.y;
    for(int i=1; i<=V; i++){
        if(i==index) continue;
        float sum = squareSum(x-vertex[i].loc.x, y-vertex[i].loc.y);
        if(sum < vertex[i].key){
            vertex[i].key = sum;
            vertex[i].parent = index;
            for(int j=1; j<=heap_size; j++){
                if(heap[j] == i) update(vertex, j);
            }
        }
    }

}
float prim(VERTEX* vertex, int start, int V){

    vertex[start].key = 0;
    makeHeap(vertex, V);
    float result=0.00f;
    while(heap_size){
        int index = extract_min(vertex);
        result += sqrt(vertex[index].key);
        relax(vertex, index, V);     
    }
    return result;
}

int main(void){

    int n;
    scanf("%d", &n);
    VERTEX *vertex = (VERTEX*)malloc(sizeof(VERTEX)*(n+1));
    for(int i=1; i<=n; i++){
        scanf("%f %f", &vertex[i].loc.x, &vertex[i].loc.y);
        vertex[i].parent = i;
        vertex[i].key = INF;
    }
    printf("%.2f",prim(vertex, 1, n));
}