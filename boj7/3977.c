#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _NODE{
    struct _NODE *next;
    int num;
}NODE;

typedef struct _NODELIST{
    NODE * head;
}NODELIST;

void addEdge(NODELIST * list, int from, int to){
    NODE * new = (NODE*)malloc(sizeof(NODE));
    new->next = list[from].head;
    new->num = to;
    list[from].head = new;
}

int degree[100002];
int out[100001];
int ssc[100001];
int d[100001];
int stack[100001];
int top=0;
int id=0;
int ssc_num=0;

int min(int a, int b){
    return a<b?a:b;
}
int dfs(NODELIST * list, int index){
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

    int t;
    scanf("%d", &t);
    while(t--){
        int N,M;
        scanf("%d %d", &N, &M);
        NODELIST * list =  (NODELIST*)malloc(sizeof(NODELIST)*(N+1));
        for(int i=1; i<=N; i++){
            list[i].head = NULL;
        }
        memset(ssc, 0, sizeof(ssc));
        memset(d, 0, sizeof(d));
        memset(stack, 0, sizeof(stack));
        memset(degree, 0, sizeof(degree));
        memset(out, 0, sizeof(out));
        top =0;
        id = 0;
        ssc_num = 0;
        for(int i=0; i<M; i++){
            int a,b;
            scanf("%d %d", &a, &b);
            addEdge(list, a, b);
        }

        for(int i=1; i<=N; i++){
            if(d[i]==0) dfs(list, i);
        }
        
        for(int i=1; i<=N; i++){
            NODE * temp = list[i].head;
            while(temp!=NULL){
            if(ssc[temp->num]!=ssc[i]) {
                degree[ssc[temp->num]]++;   
                out[ssc[i]]++;
            }
            temp = temp->next;    
            }
        }
        int zero=0, two=0;
        int object;
        for(int i=1; i<=ssc_num; i++){
            if(degree[i]>1) two++;
            else if(degree[i]==0) {
                zero++;
                object = i;
            }
        }
        for(int i=1; i<=ssc_num; i++){
            if(out[i]>1) two++;
        }
        

        if(zero!=1){
            printf("Confused\n");
        }
        
        else if(zero==1){
        
        for(int i=0; i<N; i++){
            if(ssc[i]==object) printf("%d\n", i);
        }
        }
        printf("\n");
    }
}