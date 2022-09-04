#include <stdio.h>
#include <string.h>

#define MAX 100001
int score[5][5]={
    {10, 8, 7, 5, 1},
    {8, 6, 4, 3, 1},
    {7, 4, 3, 2, 1},
    {5, 3, 2, 2, 1},
    {1, 1, 1, 1, 0}
};

char tofu[51][51];
int src = 2551, sink=2552;
int arr[2560][2560];
int size[2560];
int flow[2560][2560];
int cap[2560][2560];
int cost[2560][2560];
int dest[2560];
int visited[2560];
int inQ[2560];

int min(int a, int b){
    return a<b?a:b;
}
int bfs(){
    int ans=0;
    int result=0;

    while(1){
        memset(inQ, 0 , sizeof(inQ));
        memset(visited, 0 , sizeof(visited));

        for(int i=0; i<2560; i++) dest[i] = MAX;
        int que[100001];
        int rear=0, front=0;

        que[front++] = src;
        inQ[src] = 1;
        dest[src] = 0;
        int c = MAX;
        while(rear<front){
            int index = que[rear++];
            inQ[index] = 0;
            for(int i=0; i<size[index]; i++){
                int next = arr[index][i];
                if(dest[next]>dest[index] + cost[index][next] && cap[index][next] - flow[index][next] >0){
                    visited[next] = index;
                    dest[next] = dest[index] + cost[index][next];
                    if(!inQ[next]){
                        inQ[next] = 1;
                        que[front++] = next;
                    }
                }
            }
        }
        if(!visited[sink]) break;

        for(int i=sink ; i!=src; i=visited[i]){
            c = min(c, cap[visited[i]][i] - flow[visited[i]][i]);
        }
        for(int i=sink; i!=src; i=visited[i]){
            flow[visited[i]][i] += c;
            flow[i][visited[i]] -= c;
            result += c*cost[visited[i]][i];
        }
        ans+=c;
    }
    return result;
}
int main(void){
    int N,M;
    scanf("%d %d", &N, &M);

    memset(size, 0 ,sizeof(size));
    memset(cap, 0 ,sizeof(cap));
    memset(flow, 0, sizeof(flow));
    memset(cost, 0, sizeof(cost));

    for(int i=0; i<N; i++){
        char temp[100];
        scanf("%s", temp);
        for(int j=0; j<M; j++){
            if(temp[j] != 'F') tofu[i][j] = temp[j] - 'A';
            else tofu[i][j] = 4;           
        }
    }
    
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            int index = i*50+j;

            arr[index][size[index]++] = sink;
            arr[sink][size[sink]++] = index;
            cap[index][sink] = 1;

            if(i%2==0){
                if(j%2==0){
                    arr[src][size[src]++] = index;
                    arr[index][size[index]++] = src;
                    cap[src][index] = 1;
                }
            }
            else{
                if(j%2==1){
                    arr[src][size[src]++] = index;
                    arr[index][size[index]++] = src;
                    cap[src][index] = 1;
                }
            }
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if((i%2==0 && j%2==0) || (i%2==1 && j%2==1)){
                int index = i*50+j;
                
                if(i>0){
                    arr[index][size[index]++] = (i-1)*50+j;
                    arr[(i-1)*50+j][size[(i-1)*50+j]++] = index;
                    cap[index][(i-1)*50+j] = 1;
                    cost[index][(i-1)*50+j] = -score[tofu[i][j]][tofu[i-1][j]];
                    cost[(i-1)*50+j][index] = score[tofu[i][j]][tofu[i-1][j]];
                }
                if(i<N-1){
                    arr[index][size[index]++] = (i+1)*50+j;
                    arr[(i+1)*50+j][size[(i+1)*50+j]++] = index;
                    cap[index][(i+1)*50+j] = 1;
                    cost[index][(i+1)*50+j] = -score[tofu[i][j]][tofu[i+1][j]];
                    cost[(i+1)*50+j][index] = score[tofu[i][j]][tofu[i+1][j]];
                }
                if(j>0){
                    arr[index][size[index]++] = i*50+(j-1);
                    arr[i*50+(j-1)][size[i*50+(j-1)]++] = index;
                    cap[index][i*50+(j-1)]=1;
                    cost[index][i*50+(j-1)] = -score[tofu[i][j]][tofu[i][j-1]];
                    cost[i*50+(j-1)][index] = score[tofu[i][j]][tofu[i][j-1]];
                }
                if(j<M-1){
                    arr[index][size[index]++] = i*50+(j+1);
                    arr[i*50+(j+1)][size[i*50+(j+1)]++] = index;
                    cap[index][i*50+(j+1)]=1;
                    cost[index][i*50+(j+1)] = -score[tofu[i][j]][tofu[i][j+1]];
                    cost[i*50+(j+1)][index] = score[tofu[i][j]][tofu[i][j+1]];
                }
            }
        }
    }

    printf("%d\n", -bfs());
}