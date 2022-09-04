#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _NODE{
    struct _NODE *next;
    int num;
}NODE;

typedef struct _NODELIST{
    NODE * head;
    int cash;
    int restaurant;
}NODELIST;

typedef struct _SSCNODE{
    struct _SSCNODE *next;
    int num;
}SSCNODE;

typedef struct _SSCLIST{
    SSCNODE * head;
    int sum;
    int restaurant;
}SSCLIST;

void addEdge(NODELIST * list, int from, int to){
    NODE * new = (NODE*)malloc(sizeof(NODE));
    new->next = list[from].head;
    new->num = to;
    list[from].head = new;
}

void addTopo(SSCLIST * ssc, int from, int to){
    SSCNODE * node = ssc[from].head;
    SSCNODE * pre = NULL;
    while(node!=NULL){
        if(node->num == to) return;
        else if(node->num > to) break; 
        else if(node->num < to){
            pre = node;
            node = node->next;
        }
    }
    SSCNODE * new = (SSCNODE*)malloc(sizeof(SSCNODE));
    new->num = to;
    if(pre==NULL) {
        ssc[from].head = new;
        new->next = node;
    }
    else {
        new->next = node;
        pre->next = new;
    }

}
int degree[500001];
int d[500001];
int stack[500001];
int finish[500001];
int top=0;
int id=0;
int ssc_num=0;
int dp[500001];

int min(int a, int b){
    return a<b?a:b;
}

int max(int a, int b){
    return a>b?a:b;
}
int dfs(NODELIST * list, int index){
    d[index] = ++id;
    stack[top++] = index;

    int parent = d[index];
    NODE * temp = list[index].head;

    while(temp!=NULL){
            
        if(d[temp->num]==0) parent = min(parent, dfs(list, temp->num));
        else if(finish[temp->num]==0) parent = min(parent, d[temp->num]);
        temp = temp->next;

    }
    if(parent == d[index]){
        ssc_num++;
        while(1){
            int child = stack[--top];
            finish[child] = ssc_num;
            if(child==index) break;
        }
    }

    return parent;
}

void bfs(SSCLIST * ssc, int start){
    
    int q[500001];
    int visited[500001];
    memset(visited, 0 ,sizeof(visited));
    int rear=0, front=0;
    q[front++] = start;
    visited[start] = 1;
    while(rear<front){
        int index = q[rear++];
    
        SSCNODE * temp = ssc[index].head;
        while(temp!=NULL){
            if(visited[temp->num]==0) {
                visited[temp->num] = 1;
                q[front++] = temp->num;
                }
            degree[temp->num]++;
            temp = temp->next;
        }
    }

    rear=0, front=0;
    q[front++] = start;
    dp[start] = ssc[start].sum;
    while(rear<front){
        int index = q[rear++];
        SSCNODE * temp = ssc[index].head;
        while(temp!=NULL){
            dp[temp->num] = max(dp[temp->num], dp[index] + ssc[temp->num].sum);
            if(--degree[temp->num]==0) q[front++] = temp->num;
            temp = temp->next;
        }
    }
}
int main(void){

    int N,M;
    scanf("%d %d", &N, &M);
    NODELIST * list = (NODELIST*)malloc(sizeof(NODELIST)*(N+1));

    for(int i=1; i<=N; i++){
        list[i].head = NULL;
        list[i].cash = 0;
        list[i].restaurant = 0;
    }
    for(int i=0; i<M; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        addEdge(list, a, b);
    }
    for(int i=1;i<=N; i++){
        scanf("%d", &list[i].cash);
    }
    int S,P;
    scanf("%d %d", &S, &P);
    for(int i=0; i<P; i++){
        int a;
        scanf("%d", &a);
        list[a].restaurant = 1;
    }
    memset(d, 0, sizeof(d));
    memset(finish, 0, sizeof(finish));
    memset(dp, 0, sizeof(dp));
    memset(degree, 0 ,sizeof(degree));
    for(int i=1; i<=N; i++){
        if(d[i]==0) dfs(list, i);
    }
    SSCLIST * ssc =(SSCLIST*)malloc(sizeof(SSCLIST)*(ssc_num+1));
    for(int i=1; i<=ssc_num; i++){
        ssc[i].head = NULL;
        ssc[i].restaurant = 0;
        ssc[i].sum = 0;
    }

    for(int i=1; i<=N; i++){
        ssc[finish[i]].sum += list[i].cash;
        ssc[finish[i]].restaurant += list[i].restaurant;
        NODE * node = list[i].head;
        while(node!=NULL){
        if(finish[i]!=finish[node->num]) addTopo(ssc, finish[i], finish[node->num]);
        node = node->next;
        }

    }

    int start = finish[S];
    bfs(ssc, start);
    int answer = 0;
    for(int i=1;i<=ssc_num; i++){
        if(ssc[i].restaurant!=0) answer = max(answer, dp[i]); 
    }
    printf("%d\n", answer);
}