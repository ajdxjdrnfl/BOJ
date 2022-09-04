#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int depth[100001];
int parent[21][100001];
long long cost[21][100001];

typedef struct _NODE{
    struct _NODE * next;
    int num;
    long long weight;
}NODE;

typedef struct _NODELIST{
    NODE *head;
}NODELIST;

void addEdge(NODELIST * list, int from, int to, long long weight){
    NODE * new = (NODE*)malloc(sizeof(NODE));
    new->num = to;
    new->weight = weight;
    new->next = list[from].head;
    list[from].head = new;
}

void makeTree(NODELIST* list, int root, int N){
    memset(depth, -1, sizeof(depth));
    memset(parent, -1, sizeof(parent));
    memset(cost, -1, sizeof(cost));

    depth[root] =0;
    int que[N+1];
    int rear=0, front=0;
    que[front++] = root;
    while(rear<front){
        int index = que[rear++];
         NODE * temp = list[index].head;
         while(temp!=NULL){
             if(depth[temp->num]==-1){
                 que[front++] = temp->num;
                 parent[0][temp->num] = index;
                 depth[temp->num] = depth[index]+1;
                 cost[0][temp->num] = temp->weight;
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

void makeCost(int N){
    for(int i=1; i<=20; i++){
        for(int j=1; j<=N; j++){
            if(parent[i-1][j]!=-1) cost[i][j] = cost[i-1][j] + cost[i-1][parent[i-1][j]];
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
    if(depth[up]>depth[down]) swap(&up, &down);

    int diff = depth[down] - depth[up];
    int j=0;
    while(1){
        if(diff==0) break;
        if(diff%2==1) down = parent[j][down];
        diff/=2;
        j++; 
    }

    if(up==down) return up;

    for(int i=logs(depth[up]); i>=0 ;i--){
        if(parent[i][up]!=-1 && parent[i][up]!=parent[i][down]){
            up = parent[i][up];
            down = parent[i][down];
        }
    }
    return  parent[0][up];

}

long long one(int anc, int a, int b){
    long long result=0;
    int diff = depth[a] - depth[anc];
    int j=0;
    while(1){
        if(diff==0) break;
        if(diff%2==1){
            result += cost[j][a];
            a = parent[j][a];
        }
        diff/=2;
        j++;

    }

    diff = depth[b] - depth[anc];
    j=0;
    while(1){
        if(diff==0) break;
        if(diff%2==1){
            result += cost[j][b];
            b = parent[j][b];
        }
        diff/=2;
        j++;
    }
    return result;

}

int two(int anc, int up, int down, int k){

    
    int diff, index;
    if(k<=depth[down]-depth[anc]+1) {
        diff = k-1;
        index = down;
    }
    else {
        diff = (depth[up] - depth[anc]+1) - (k - (depth[down]-depth[anc]+1))-1;
        index = up;
    } 

    int j = 0;
    while(1){
        if(diff==0) break;
        if(diff%2==1) index = parent[j][index];
        diff/=2;
        j++;
    }
    return index;
    
}

int main(void){
    int N,M;
    scanf("%d", &N);
    NODELIST * list = (NODELIST*)malloc(sizeof(NODELIST)*(N+1));
    for(int i=0; i<N-1; i++){
        int a,b;
        long long c;
        scanf("%d %d %lld", &a, &b, &c);
        addEdge(list, a, b, c);
        addEdge(list, b, a, c);
    }

    makeTree(list,1,N);
    makeParent(N);
    makeCost(N);
    
    scanf("%d", &M);
    for(int i=0; i<M; i++){
        int num;
        scanf("%d", &num);
        if(num==1){
            int a,b, anc;
            scanf("%d %d", &a, &b);
            anc = lca(a,b);
            
            printf("%lld\n",one(anc,a,b));
        }
        else if(num==2){
            int a,b,c;
            scanf("%d %d %d", &a, &b,&c);
            int anc = lca(a,b);
        
            printf("%d\n", two(anc, b,a,c));
        
        }
    }
}