#include <stdio.h>
#include <string.h>

#define MAX 100001

int arr[810][810];
int flow[810][810];
int cap[810][810];
int visited[810];
int cost[810][810];
int size[810];
int dest[810];
int inQ[810];

int result=0;
int min(int a, int b){
    return a<b?a:b;
}
int bfs(int start, int end){
    
    int ans=0;
    
    while(1){
        memset(visited,0 , sizeof(visited));
        memset(inQ, 0, sizeof(inQ));
        for(int i=0; i<810; i++){
            dest[i] = MAX;
        }
        int rear=0, front=0;
        int que[100001];
        int c = MAX;
        que[front++] = start;
        dest[start] = 0;
        inQ[start] = 1;
        
        while(rear<front){
            int index = que[rear++];
            for(int i=0; i<size[index]; i++){
                int next = arr[index][i];
                if(cap[index][next] - flow[index][next]>0 && dest[next] > dest[index] + cost[index][next]){
                        dest[next] = dest[index] + cost[index][next];
                        visited[next] = index;
                        if(!inQ[next]){
                            visited[next] = index;
                            que[front++] = next;
                        }                        
                }
            }
        }
        if(!visited[end]) break;
        
        for(int i=end; i!=start; i=visited[i]){
            c = min(c, cap[visited[i]][i] - flow[visited[i]][i]);
        }
        for(int i=end; i!=start; i=visited[i]){
            result += c*cost[visited[i]][i];
            flow[visited[i]][i] += c;
            flow[i][visited[i]] -= c;
        }
        ans += c;
    }

    return ans;
}
int main(void){

    int N,M;
    int start = 801, end = 802;
    scanf("%d %d", &N, &M);
    
    memset(arr, 0 , sizeof(arr));
    memset(flow, 0, sizeof(flow));
    memset(cap, 0, sizeof(cap));
    memset(cost, 0, sizeof(cost));
    memset(size, 0, sizeof(size));

    for(int i=1; i<=N; i++){
        int num;
        scanf("%d", &num);
        for(int j=1; j<=num; j++){
            int a,b;
            scanf("%d %d", &a, &b);
            arr[i][size[i]++] = a+400;
            arr[a+400][size[a+400]++] = i;
            cap[i][a+400] = 1;
            cost[i][a+400] = -b;
            cost[a+400][i] = b;
        }
    }

    for(int i=0; i<810; i++){
        dest[i] = MAX;
    }
    for(int i=1; i<=N; i++){
        arr[start][size[start]++] = i;
        arr[i][size[i]++] = start;
        cap[start][i] = 1;
    }
    for(int i=1; i<=M; i++){
        arr[i+400][size[i+400]++] = end;
        arr[end][size[end]++] = i+400;
        cap[i+400][end] = 1;
    }
    printf("%d\n", bfs(start, end));
    printf("%d\n", -result);
}