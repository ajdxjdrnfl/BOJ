#include <stdio.h>
#include <stdlib.h>

#define INF 10
int loc[10][10];
int visited[10][10];
int is_num=1;

int edge[7][7];
int parent[7];
int rank[7];

typedef struct _EDGE{
    int u;
    int v;
    int weight;
}EDGE;

EDGE bridge[31];
int bridge_size=0;

int checkP(int index){
    while(index!=parent[index]) index = parent[index];
    return index;
}
void island(int i, int j, int N, int M, int num){

 
    if(i+1<N && loc[i+1][j]==1 && visited[i+1][j]==0){
        visited[i+1][j] = num;
        island(i+1, j, N, M, num);
    }
    if(j+1<M && loc[i][j+1]==1 && visited[i][j+1]==0){
        visited[i][j+1] = num;
        island(i, j+1, N,M, num);
    }
    if(i-1>=0 && loc[i-1][j]==1 && visited[i-1][j]==0){
        visited[i-1][j] = num;
        island(i-1, j, N, M, num);
    }
    if(j-1>=0 && loc[i][j-1]==1 && visited[i][j-1]==0){
        visited[i][j-1] = num;
        island(i, j-1, N, M, num);
    }

}

void findEdge(int i, int j, int N, int M){
    int right=0, left=0, up=0, down=0;
    for(int k=1; j+k<M; k++){
        if(visited[i][j+k]==visited[i][j]) break;
        if(visited[i][j+k] != 0 && visited[i][j+k] != visited[i][j] ){
            if(right<=1) break;
            else if(edge[visited[i][j]][visited[i][j+k]]>right){
                edge[visited[i][j]][visited[i][j+k]]=right;
                edge[visited[i][j+k]][visited[i][j]]=right;
                break;
            }
            break;
        } 
        else right++;
    }
    for(int k=1; j-k>=0; k++){
        if(visited[i][j-k]==visited[i][j]) break;
        if(visited[i][j-k] != 0 && visited[i][j-k] != visited[i][j]){
            if(left<=1) break;
            else if(edge[visited[i][j]][visited[i][j-k]]>left){
                edge[visited[i][j]][visited[i][j-k]]=left;
                edge[visited[i][j-k]][visited[i][j]]=left;
                break;
            }
            break;
        }
        else left++;
    }
    for(int k=1; i+k<N; k++){
        if(visited[i+k][j]==visited[i][j]) break;
        if(visited[i+k][j]!=0 && visited[i+k][j] != visited[i][j]){
            if(down<=1) break;
            else if(edge[visited[i][j]][visited[i+k][j]]>down){
                edge[visited[i][j]][visited[i+k][j]]=down;
                edge[visited[i+k][j]][visited[i][j]]=down;
                break;
            }
            break;
        }
        else down++;
    }
    
    for(int k=1; i-k>=0; k++){
        if(visited[i-k][j]==visited[i][j]) break;
        if(visited[i-k][j]!=0 && visited[i-k][j] != visited[i][j]){
            if(up<=1) break;
            else if(edge[visited[i][j]][visited[i-k][j]]>up){
                edge[visited[i][j]][visited[i-k][j]]=up;
                edge[visited[i-k][j]][visited[i][j]]=up;
                break;
            }
            break;
        }
        else up++;
    }
}

int comp(const void*a, const void*b){
    EDGE pa = *(EDGE*)a; 
    EDGE pb = *(EDGE*)b;

    if(pa.weight < pb.weight) return -1;
    else if(pa.weight > pb.weight) return 1;
    return 0;
}
int main(void){
    int N,M, result=0;
    scanf("%d %d", &N, &M);
    
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            scanf("%d", &loc[i][j]);
        }
    }
    
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++ ){
            if(loc[i][j]==1 && visited[i][j]==0){
                visited[i][j] = is_num;
                island(i, j, N, M, is_num++);
            }                   
        }
    }
    for(int i=1; i<is_num; i++){
        for(int j=1; j<is_num; j++) edge[i][j] = INF;
    }
    for(int i=1; i<is_num; i++){
        parent[i] = i;
        rank[i] = 1;
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(loc[i][j]==1) findEdge(i, j, N, M); 
        }
    }
    
    for(int i=1; i<is_num; i++){
        for(int j=i+1; j<is_num; j++){
            if(edge[i][j] != INF) {
                
                bridge[bridge_size].u = i;
                bridge[bridge_size].v = j;
                bridge[bridge_size++].weight = edge[i][j];
            }
        }
    }
    qsort(bridge, bridge_size, sizeof(EDGE), comp);
    
    for(int i=0; i<bridge_size; i++){
        int a = checkP(bridge[i].u);
        int b = checkP(bridge[i].v);
        if(a==b) continue;
        else{
            result+=bridge[i].weight;
            if(rank[a] < rank[b]) parent[a] = b;
            else{
                parent[b] = a;
                if(rank[a]==rank[b]) rank[a]++;
            }
        }
    }
    int temp=0;
    for(int i=1; i<is_num; i++){
        if(checkP(i)==i) temp++;
    }
    if(temp==1) printf("%d\n", result);
    else printf("-1\n");

    
}