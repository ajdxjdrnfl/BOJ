#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _NODE{
    struct _NODE *next;
    int num;
}NODE;

typedef struct _NODELIST{
    NODE * head;
}NODELIST;

typedef struct _SSC{
    int num;
    struct _SSC * next;
}SSC;

typedef struct _SSCLIST{
    SSC * head;
    int degree;
}SSCLIST;

void addEdge(NODELIST * list, int from, int to){
    NODE * new = (NODE*)malloc(sizeof(NODE));
    new->next = list[from].head;
    new->num = to;
    list[from].head = new;
}

int ssc[100001];
int d[100001];

int stack[100001];
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

        if(d[temp->num]==0) parent = min(parent , dfs(list, temp->num));
        else if(ssc[temp->num]==0) parent = min(parent , d[temp->num]);

        temp = temp->next;
    }

    if(parent==d[index]){
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
        NODELIST * list = (NODELIST*)malloc(sizeof(NODE)*(N+1));
        for(int i=1; i<=N; i++){
            list[i].head = NULL;
        }

        memset(ssc, 0, sizeof(ssc));
        memset(d, 0, sizeof(d));
        memset(stack, 0, sizeof(stack));
        top = 0;
        id = 0;
        ssc_num  = 0;
        for(int i=0; i<M; i++){
            int a,b;
            scanf("%d %d", &a, &b);
            addEdge(list, a, b);
        }
        for(int i=1; i<=N; i++){
            if(d[i]==0) dfs(list, i);
        }
        SSCLIST * sscList = (SSCLIST*)malloc(sizeof(SSCLIST)*(ssc_num+1));

        for(int i=1; i<=ssc_num; i++){
            sscList[i].head = NULL;
            sscList[i].degree = 0;
        }
       
        for(int i=1; i<=N; i++){
            NODE * temp = list[i].head;
            while(temp!=NULL){
                if(ssc[temp->num]!=ssc[i]) sscList[ssc[temp->num]].degree++;
                temp = temp->next;
            }
        }
        int result = 0 ;
        
        for(int i=1;i<=ssc_num; i++){
            if(sscList[i].degree==0) result++;
        
        }
        printf("%d\n", result);
    }
}