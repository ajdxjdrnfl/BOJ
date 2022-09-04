#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _NODE{
    struct _NODE * next;
    int num;
}NODE;

typedef struct _NODELIST{
    NODE * head;
    int visited;
}NODELIST; 

NODELIST * makeTree(int V){
    NODELIST* list = (NODELIST*) malloc(sizeof(NODELIST)*(V+1));
    
    for(int i=1; i<=V; i++){
        list[i].head = NULL;
        list[i].visited = 0;
    }
    return list;
}

void addEdge(NODELIST* list, int from, int to){
    NODE * node = (NODE*)malloc(sizeof(NODE));
    node->next = list[from].head;
    node->num = to; 
    list[from].head = node;
}

int matchParent(int *parent, int a, int b,int V){

    while(parent[a]!=0){
        
        a = parent[a];
    }
    while(parent[b]!=0){
        
        b = parent[b];
    }
    if(a==b) return 1;
    else return 0;
}

int checkTree(NODELIST* list, int V){
    int result=0;
    for(int i=1; i<=V; i++){
        if(list[i].visited==0){
            int answer=0;
            int que[V+1];
            int parent[V+1];
            memset(parent, 0, sizeof(parent));
            int rear=-1, front=-1;
            que[++front] = i;
            list[i].visited=1;
            parent[i] = 0;
            while(rear<front){
            int temp = que[++rear];
            NODE * node = list[temp].head;
            while(node!=NULL){
                if(list[node->num].visited == 0){
                    list[node->num].visited=1;
                    que[++front] = node->num;
                    parent[node->num] = temp;
                }
                else if(list[node->num].visited == 1 && parent[temp] != node->num && matchParent(parent, node->num, temp,V)==1) answer = 1;
                node = node->next;
            }
            }
            if(answer==0) result++; 
        }
    }
    return result;

}

int main(void){
    int i=1;
    while(1){
        int a,b,T;
        scanf("%d %d", &a, &b);
        if(a==0 && b==0) break;
        NODELIST * list = makeTree(a);
        for(int i=1; i<=b; i++){
            int c,d;
            scanf("%d %d", &c, &d);   
            addEdge(list, c,d);
            addEdge(list, d,c);
        }
        T = checkTree(list, a);
        if(T==0) printf("Case %d: No trees.\n", i);
        else if(T==1)printf("Case %d: There is one tree.\n",i);
        else printf("Case %d: A forest of %d trees.\n",i,T);
        i++;
    }
}