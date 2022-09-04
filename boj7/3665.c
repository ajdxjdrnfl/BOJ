#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _NODE{
    struct _NODE * next;
    int num;
}NODE;

typedef struct _NODELIST{
    NODE * head;
    int degree;
}NODELIST;

int rank[502];

void addEdge(NODELIST * list, int from ,int to){
    NODE * new = (NODE*)malloc(sizeof(NODE));
    new->num = to;
    new->next = list[from].head;
    list[from].head = new;
    list[to].degree++;
}

void changeEdge(NODELIST * list, int a, int b){

    NODE * temp = list[a].head;
    NODE * last = NULL;
    while(temp!=NULL){
        if(temp->num == b){
            if(last == NULL) list[a].head = temp->next;
            else last->next = temp->next;
            list[b].degree--;
            addEdge(list,b,a);
            return;
        }
        last = temp;
        temp = temp->next;
    }
    temp = list[b].head;
    last = NULL;

    while(temp!=NULL){
        if(temp->num == a){
            if(last == NULL) list[b].head = temp->next;
            else last->next = temp->next;
            list[a].degree--;
            addEdge(list,a,b);
            return;
        }
        last = temp;
        temp = temp->next;
    }

    return;
}

int main(void){

    int test;
    scanf("%d", &test);
    while(test--){

        memset(rank, 0, sizeof(rank));
        int n,m;
        scanf("%d", &n);
        NODELIST * list = (NODELIST*)malloc(sizeof(NODELIST)*(n+1));
        for(int i=1; i<=n; i++){
            list[i].degree = 0;
            list[i].head = NULL;
        }
        for(int i=1; i<=n; i++){ 
            scanf("%d", &rank[i]);
            for(int j=i-1; j>=1; j--){
                addEdge(list, rank[i], rank[j]);   
            } 
            
        }
        
        scanf("%d", &m);
        for(int i=0; i<m; i++){
            int a, b;
            scanf("%d %d", &a, &b);
            changeEdge(list, a, b);
        }
        
        int que[502];
        int rear=0, front=0;
        for(int i=1; i<=n; i++){
            if(list[i].degree==0) que[front++] = i;
        }
        while(rear<front){
            int index = que[rear++];
            NODE * temp = list[index].head;
           
            while(temp!=NULL){
        
                list[temp->num].degree--;
                if(list[temp->num].degree == 0 ) que[front++] = temp->num;
                temp = temp->next;
            }
        }
        if(front!=n){
            printf("IMPOSSIBLE\n");
        }
        else{
            for(int i=front-1; i >=0; i--){
                printf("%d ", que[i]);
            }
            printf("\n");
        }
            
    }
}