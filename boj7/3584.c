#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
    struct _NODE *parent;
    int num;
}NODE;

typedef struct _NODELIST{
    NODE * head;
}NODELIST;

void addEdge(NODELIST * list, int from, int to){
    list[to].head->parent = list[from].head;
}
int main(void){

    int t;
    scanf("%d", &t);
    while(t--){
        int N;
        scanf("%d", &N);
        NODELIST * list = (NODELIST*)malloc(sizeof(NODELIST)*(N+1));

        for(int i=1; i<=N; i++){
            NODE * new = (NODE*)malloc(sizeof(NODE));
            new->parent =NULL;
            new->num = i;
            list[i].head = new;
            
        }

        for(int i=0; i<N-1; i++){
            int a, b;
            scanf("%d %d", &a, &b);
            addEdge(list,a,b);
        }
        int a, b;
        scanf("%d %d", &a, &b);

        int first = b;
        while(1){
            if(a==list[b].head->num) {
                printf("%d\n",a);
                break;
            }
            if(list[b].head->parent!=NULL){
                b = list[b].head->parent->num;
            }
            else{
                b = first;
                a = list[a].head->parent->num;
            }
        }
    }
}