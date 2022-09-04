#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parent[21][100001];
int largest[21][100001];
int smallest[21][100001];
int depth[100001];

typedef struct _NODE{
    struct _NODE * next;
    int num;
    int weight;
}NODE;

typedef struct _NODELIST{
    NODE * head;
}NODELIST;

void addEdge(NODELIST *list, int from, int to, int weight){

    NODE * new = (NODE*)malloc(sizeof(NODE));
    new->weight = weight;
    new->num = to;
    new->next = list[from].head;
    list[from].head = new;
}

void makeTree(NODELIST* list, int root, int N){
    memset(parent, -1, sizeof(parent));
    memset(depth, -1, sizeof(depth));
    depth[root] = 0;
    int rear=0, front =0;
    int que[100001];
    que[front++] = root;
    for(int i=0; i<=20; i++){
        largest[i][root] = -1;
        smallest[i][root] = 1000001;
    }
    while(rear<front){
        int index = que[rear++];
        NODE * temp = list[index].head;
    while(temp!=NULL){
        
        if(depth[temp->num]==-1){
            depth[temp->num] = depth[index]+1;
            largest[0][temp->num] = temp->weight;
            smallest[0][temp->num] =  temp->weight;
            parent[0][temp->num] = index;
            que[front++] = temp->num;
        }
        temp = temp->next;
    }
    }
    

}

void makeParent(int N){
    for(int i=1; i<=20; i++){
        for(int j=1; j<=N; j++){
            if(parent[i-1][j]!=-1) parent[i][j] = parent[i-1][parent[i-1][j]];
        }
    }

}
int min(int a,int b){
    return a>b?b:a;
}

int max(int a, int b){
    return a>b?a:b;
}
void makeNetwork(NODELIST *list, int N){
    for(int i=1; i<=20; i++){
        for(int j=1; j<=N; j++){
            if(parent[i-1][j]!=-1){
                smallest[i][j] = min(smallest[i-1][j], smallest[i-1][parent[i-1][j]]);
                largest[i][j] = max(largest[i-1][j], largest[i-1][parent[i-1][j]]);
            }
            else {
               largest[i][j] = -1;
                smallest[i][j] = 1000001;
            }
        }
    }
}
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int logs(int N){
    
    if(N/2!=0) return 1+logs(N/2);
    else return 0;
}
int lca(int up, int down){
    if(depth[up] > depth[down]) swap(&up, &down);

    int diff = depth[down] - depth[up];
    int j=0;

    while(1){
        if(diff==0) break;
        if(diff%2==1) down = parent[j][down];
        diff = diff/2;
        j++;
    }

    if(up==down) return up;
   
    for(int i=logs(depth[up]); i>=0; i--){
        if(parent[i][up]!=-1 && parent[i][up] != parent[i][down]){
            up = parent[i][up];
            down = parent[i][down];
        }
    }
    up = parent[0][up];
    return up;
    
}


void findNetwork(NODELIST *list, int anc, int a, int b){
    int small = 1000001, larg = -1;

    int diff = depth[a]- depth[anc];
    int j =0;
    while(1){
        if(diff==0) break;
        if(diff%2==1) {
            if(largest[j][a]>larg) larg = largest[j][a];
            if(smallest[j][a]<small) small = smallest[j][a];
            a = parent[j][a];
        }
        diff = diff/2;
        j++;
    }
    diff = depth[b]-depth[anc];
    j=0;
    while(1){
        if(diff==0) break;
        if(diff%2==1) {
            if(largest[j][b]>larg) larg = largest[j][b];
            if(smallest[j][b]<small) small = smallest[j][b];
            b = parent[j][b];
        }
        diff = diff/2;
        j++;
    }
    printf("%d %d\n", small, larg);
}

int main(void){

    int N,K;
    scanf("%d", &N);
    NODELIST * list = (NODELIST*)malloc(sizeof(NODELIST)*(N+1));
    for(int i=1; i<=N; i++){
        list[i].head = NULL;
    }
    for(int i=0; i<N-1; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        addEdge(list,a,b,c);
        addEdge(list,b,a,c);
    }

    makeTree(list, 1, N);
    makeParent(N);
    makeNetwork(list, N);

    scanf("%d", &K);
    for(int i=0; i<K; i++){
        int a,b, anc;
        scanf("%d %d", &a, &b);
        anc = lca(a,b);
        
        findNetwork(list, anc,a,b);
    }
}