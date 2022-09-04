#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int visited[100001];
int v;
typedef struct _NODE{
    int num;
    int weight;
    struct _NODE * next;
}NODE;

typedef struct _NODELIST{
    NODE * head;
    int largest;
    int next;
}NODELIST;

void addEdge(NODELIST *list, int from, int to, int weight){
    NODE* new = malloc(sizeof(NODE));
    new->num = to;
    new->weight = weight;
    new->next = list[from].head;
    list[from].head = new;
}

NODELIST * createList(int size){
    NODELIST* list = (NODELIST*)malloc(sizeof(NODELIST)*(size+1));
    for(int i=1; i<=size; i++){
        list[i].largest = -1;
        list[i].head = NULL;
        list[i].next = 0;
    }
    return list;
}

int max(int a, int b){
    return a>b?a:b;
}
int dfs(NODELIST * list, int index){

    int largest = 0;
    visited[index] = 1;
    NODE * node = list[index].head;
    while(node!=NULL){
        if(visited[node->num]==0) {
            int temp = dfs(list, node->num);
            if(largest < node->weight + temp){
                largest = temp + node->weight;
                list[index].next = node->num;
            }
        } 
        node = node->next;
    }

    return largest;
}
int main(void){

    int N;
    int result = -1;
    scanf("%d", &N);
    NODELIST* list = createList(N);
    for(int i=1; i<=N-1; i++){
        int a,b,c;
        scanf("%d %d %d", &a, &b, &c);
        addEdge(list, a, b, c);
        addEdge(list, b, a, c);
    }
    dfs(list, 1);
    memset(visited, 0, sizeof(visited));
    int i =1;
    while(1){
        
        if(list[i].next==0){
            v=i; break;
        } 
        i = list[i].next;
    }
  
    result =dfs(list, v);

    printf("%d\n", result);

}