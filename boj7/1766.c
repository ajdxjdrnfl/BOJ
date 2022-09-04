#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
    struct _NODE *next;
    int num;
}NODE;

typedef struct _NODELIST{
    NODE * head;
    int degree;
}NODELIST;

int heap[32001];
int heap_size;

void addEdge(NODELIST *list , int from, int to){
    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->num = to;
    node->next = list[from].head;
    list[from].head = node;
    list[to].degree++;
}

void swap(int a, int b){
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}
void heapify(int index){
    
    int shortest = index;
    if(index*2<=heap_size && heap[index*2] < heap[shortest]) shortest = index*2;
    if(index*2+1<=heap_size && heap[index*2+1] < heap[shortest]) shortest = index*2+1;
    
    if(shortest != index){
        swap(shortest, index);
        heapify(shortest);
    }
}

int extract_min(){
    int temp = heap[1];
    heap[1] = heap[heap_size--];
    heapify(1);
    return temp;
}

void insert(int num){
    heap[++heap_size] = num;
    for(int i=heap_size/2; i>=1; i=i/2){
        heapify(i);
    }
}
void relax(NODELIST * list, int index){
    NODE * temp = list[index].head;

    while(temp!=NULL){
        if(--list[temp->num].degree==0) insert(temp->num);
        temp = temp->next;
    }
}
void minheap(NODELIST * list, int size){
    heap_size = 0;
    for(int i=1; i<=size; i++){
       if(list[i].degree == 0) insert(i);
    }
    
    while(heap_size!=0){
        int index = extract_min();
        printf("%d ", index);
        relax(list, index);
    }
    printf("\n");
}
int main(void){

    int N,M;
    scanf("%d %d", &N, &M);
    NODELIST * list  = (NODELIST*)malloc(sizeof(NODELIST)*(N+1));
    for(int i=1; i<=N; i++){
        list[i].head = NULL;
        list[i].degree = 0;
    }
    for(int i=0; i<M; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        addEdge(list, a, b);
    }
    
    minheap(list, N);
   
}