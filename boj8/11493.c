#include <stdio.h>
#include <string.h>

#define BLACK 0
#define WHITE 1
#define MAX 1000001
int v[501];
int coin[501];
int arr[1010][1010];
int size[1010];
int cost[1010][1010];
int dest[1010];
int cap[1010][1010];
int flow[1010][1010];
int visited[1010];
int inQ[1010];
int start = 1001, end = 1002;

int min(int a, int b){
    return a<b?a:b;
}

int bfs(int start, int end){
    int ans=0;
    int result=0;

    while(1){
        memset(visited, 0 , sizeof(visited));
        memset(inQ, 0, sizeof(inQ));

        for(int i=0; i<1010; i++) dest[i] = MAX;

        int rear=0, front=0;
        int que[100001];
        que[front++] = start;
        inQ[start] = 1;
        dest[start] = 0;
        int c = MAX;
        while(rear<front){
            int index = que[rear++];
            inQ[index] = 0;
            for(int i=0; i<size[index]; i++){
                
                int next = arr[index][i];
             
                if(cap[index][next] - flow[index][next]>0 && dest[next] > dest[index] + cost[index][next]){
                    dest[next] = dest[index] + cost[index][next];
                    visited[next] = index;
                    if(!inQ[next]){
                        inQ[next] = 1;
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
      
        ans+=c;
    }
    return result;
}
int main(void){
    int T;
    scanf("%d", &T);
    while(T--){

        int n,m;
        scanf("%d %d",&n,&m);

        memset(size, 0, sizeof(size));
        memset(v, 0, sizeof(v));
        memset(coin, 0, sizeof(coin));
        memset(arr, 0 , sizeof(arr));
        memset(dest, 0 , sizeof(dest));
        memset(cost ,0 , sizeof(cost));
        memset(cap, 0 , sizeof(cap));
        memset(flow, 0 ,sizeof(flow));
        
        for(int i=1; i<=n; i++){
            arr[i][size[i]++] = i+500;
            arr[i+500][size[i+500]++] = i;
            cap[i][i+500] = MAX;
        }
        for(int i=0; i<m; i++){
            int a,b;
            scanf("%d %d", &a, &b);

            arr[a+500][size[a+500]++] = b;
            arr[b][size[b]++] = a+500;
            cap[a+500][b] = MAX;
            cost[a+500][b] = 1;
            cost[b][a+500] = -1;

            arr[b+500][size[b+500]++] = a;
            arr[a][size[a]++] = b+500;
            cap[b+500][a] = MAX;
            cost[b+500][a] = 1;
            cost[a][b+500] = -1;
        }

        for(int i=1; i<=n; i++){
            scanf("%d", &v[i]);
        }
        for(int i=1; i<=n; i++){
            scanf("%d", &coin[i]);
        }

        for(int i=1; i<=n; i++){
            if(v[i]!=coin[i]){
                if(v[i]==BLACK){
                    arr[start][size[start]++] = i;
                    arr[i][size[i]++] = start;
                    cap[start][i] = 1;
                }
                else{
                    arr[i+500][size[i+500]++] = end;
                    arr[end][size[end]++] = i+500;
                    cap[i+500][end] = 1;
                }
            }
        }
        printf("%d\n", bfs(start, end));
    }
}