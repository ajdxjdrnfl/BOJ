#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _NODE{
    struct _NODE *next;
    int num;
}NODE;
typedef struct _NODELIST{
    NODE *head;
}NODELIST;

void addEdge(NODELIST *list, int from, int to){
    NODE * node = list[from].head;
    NODE * pre = NULL;
    while(node!=NULL){
        if(node->num == to) return;
        else if(node->num > to) break; 
        else if(node->num < to){
            pre = node;
            node = node->next;
        }
    }
    NODE * new = (NODE*)malloc(sizeof(NODE));
    new->num = to;
    if(pre==NULL) {
        list[from].head = new;
        new->next = node;
    }
    else {
        new->next = node;
        pre->next = new;
    }
}
int d[20001];
int ssc[20001];
int stack[20001];
int top=0;
int id=0;
int ssc_num=0;

int min(int a, int b){
    return a<b?a:b;
}
int dfs(NODELIST *list, int index){
    d[index] = ++id;
    stack[top++] = index;

    int parent = d[index];
    NODE * temp = list[index].head;
    while(temp!=NULL){
       
        if(d[temp->num]==0) parent = min(parent, dfs(list, temp->num));
        else if(ssc[temp->num]==0) parent = min(parent, d[temp->num]);  
        temp = temp->next;
    }

    if(parent == d[index]){
        ssc_num++;
        while(1){
            int child = stack[--top];
            ssc[child] = ssc_num;
            if(child == index) break;
        }

    }
    return parent;
    
}

int main(void){


   
    int N,M;
    while(scanf("%d %d", &N, &M)!=EOF){
    NODELIST * list = (NODELIST*)malloc(sizeof(NODELIST)*(2*N+1));
    memset(d, 0, sizeof(d));
    memset(ssc, 0, sizeof(ssc));
    top = 0;
    id = 0;
    ssc_num = 0;
    for(int i=0; i<M; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        addEdge(list, -a+N, b+N);
        addEdge(list, -b+N, a+N);
        
    }

    for(int i=0; i<=2*N; i++){
        if(i<N){
             if(d[i+N+1]==0) dfs(list, i+N+1);
        }
        if(i==N) continue;
        else{
             if(d[2*N-i]==0) dfs(list, 2*N-i);
        }
    }
    

    for(int i=1; i<=N; i++){
        
        if(ssc[i+N]==ssc[-i+N]){
            printf("no\n");
            break;
        }
        if(i==N){ 
            if(ssc[1+N]<ssc[-1+N]) printf("yes\n");
            else printf("no\n");
        }
    }
    }
}