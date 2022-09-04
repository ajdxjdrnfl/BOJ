#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _NODE{
    struct _NODE * next;
    int num;
}NODE;

typedef struct _NODELIST{
    NODE * head;
}NODELIST;

int depth[100001];
int parent[21][100001];
int MAX;
void addEdge(NODELIST *list, int from, int to){

    NODE *new = (NODE*)malloc(sizeof(NODE));
    new->num = to;
    new->next = list[from].head;
    list[from].head = new;
}

void makeTree(NODELIST * list, int root, int N){

    int visited[N+1];
    memset(visited, 0, sizeof(visited));
    int que[N+1];
    int rear=0, front=0;
    que[front++] = root;
    visited[root] = 1;

    while(rear<front){
        int index = que[rear++];
        NODE * temp = list[index].head;
        while(temp!=NULL){
            if(visited[temp->num]==0) {
                que[front++] = temp->num;
                depth[temp->num] = depth[index]+1;
                parent[0][temp->num] = index;
                visited[temp->num] = 1;
            }
            temp = temp->next;
        }

    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int makeParent(int k, int n){
    
    if(k==0) return parent[0][n];
    if(n<0) return -1;
    if(parent[k][n]!=-1) return parent[k][n];
    
    parent[k][n] = makeParent(k-1, makeParent(k-1, n));
    return parent[k][n];
}

int logs(int num){
    if(num/2!=0) return 1 + logs(num/2);
    else return 0;
}

int lca(int up, int down){
    if(depth[up] > depth[down]) swap(&up,&down);
    int dist = depth[down]-depth[up];
    
    int j = 0;
    while(1){
        
        if(dist==0) break;
        if(dist%2==1) down = makeParent(j, down);
        dist = dist/2;
        j++;
 
    }
    
    if(up == down) return up;
    j = 0;
  
    for(int i=logs(depth[up]); i>=0; i--){
        if(makeParent(i,up)!=-1 && makeParent(i,up)!=makeParent(i, down)){
            up = makeParent(i, up);
            down = makeParent(i, down);
        }
    }
    
    return makeParent(0, up);
    

}

int main(void){
    int N,M;
    scanf("%d", &N);
    depth[1] = 0;
    NODELIST *list = (NODELIST*)malloc(sizeof(NODELIST)*(N+1));
    for(int i=1; i<=N; i++){
        list[i].head = NULL;
    }

    memset(parent, -1, sizeof(parent));
    memset(depth, 0, sizeof(depth));
    for(int i=0; i<N-1; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        addEdge(list ,a, b);
        addEdge(list, b, a);
    }
    makeTree(list, 1, N);
    
    
    
    scanf("%d", &M);
    for(int i=0; i<M; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", lca(a,b));
    }
}