#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _NODE{
    struct _NODE * next;
    int num;
}NODE;

typedef struct _NODELIST{
    NODE *head;
}NODELIST;

void addEdge(NODELIST * list, int from, int to){
    NODE * new = (NODE*)malloc(sizeof(NODE));
    new->num = to;
    new->next = list[from].head;
    list[from].head = new;
}


int stack[10001];
int top=0;
int id=0;
int order[10001];
int ssc[10001];
int visited[10001];

int min(int a, int b){
    return a<b?a:b;
}
int dfs(NODELIST* list, int index, int V){
    
    order[index]=++id;
    stack[top++]=index;

    int parent = order[index];
    NODE * temp = list[index].head;
    while(temp!=NULL){

        if(order[temp->num]==0) parent = min(parent, dfs(list, temp->num, V));
        else if(ssc[temp->num]==0) parent= min(parent, order[temp->num]);  
        temp = temp->next;
    }
    if(parent == order[index]){
        while(1){
        int child = stack[--top];
        ssc[child] = index;
        if(child==index) break;
        }
    }
    return parent;
    
} 

int main(void){

    int V,E;
    scanf("%d %d", &V, &E );

    NODELIST* list = (NODELIST*)malloc(sizeof(NODELIST)*(V+1));
    for(int i=1; i<=V; i++)  list[i].head =NULL;
    
    for(int i=0; i<E; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        addEdge(list, a, b);
    }
    memset(ssc, 0, sizeof(ssc));
    
    for(int i=1; i<=V; i++){
        if(order[i]==0){
            dfs(list, i, V);
        }
    }
    int result = 0;
    memset(visited, 0 , sizeof(visited));
    for(int i=1; i<=V; i++){
        if(visited[ssc[i]]==0){
            result++;
            visited[ssc[i]]=1;
        }
    }
    printf("%d\n", result);
    memset(visited, 0 , sizeof(visited));
    for(int i=1; i<=V; i++){
        if(visited[ssc[i]]==0){
            for(int j=1; j<=V; j++){
                if(ssc[i]==ssc[j]) printf("%d ", j);
            }
            visited[ssc[i]]=1;
            printf("-1\n");
        }
    }
    
}
