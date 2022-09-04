#include <stdio.h>
#include <string.h>

int col[51];
int row[51];
int flow[110][110];
int cap[110][110];
int arr[110][110];
int size[110];
int visited[110];
int l,r,m;
int N;
#define MAX 100001
void init(int th){
    memset(flow, 0, sizeof(flow));
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cap[i][j+50] = th;
        }
    }
}

int min(int a, int b){
    return a<b?a:b;
}
int bfs(int th, int start, int end){
    
    init(th);
    int ans = 0;
    while(1){
        int rear= 0 ,front = 0;
        int que[100001];
        que[front++] = start;
        int c = MAX;
        memset(visited,0, sizeof(visited));
        while(rear<front){
            int index = que[rear++];
            for(int i=0; i<size[index]; i++){
                int next = arr[index][i];
                if(!visited[next] && cap[index][next] - flow[index][next] > 0){
                    visited[next] = index;
                    que[front++] = next;
                    if(next==end) break;
                }
            }
        }
        if(!visited[end])break;
        for(int i=end; i!=start; i=visited[i]){
            c = min(c, cap[visited[i]][i] - flow[visited[i]][i]);
        }
        for(int i=end; i!=start; i=visited[i]){
            flow[visited[i]][i] += c;
            flow[i][visited[i]] -= c;
        }
        ans += c;
    }
    return ans;
}
int main(void){


    int start = 101, end = 102;
    int sum=0;
    memset(flow, 0, sizeof(flow));
    memset(cap, 0 ,sizeof(cap));
    memset(size, 0, sizeof(size));
    scanf("%d", &N);
    for(int i=1; i<=N; i++){
        scanf("%d", &row[i]);
        sum += row[i];
    }
    for(int i=1; i<=N; i++){
        scanf("%d", &col[i]);
    }

    for(int i=1; i<=N; i++){
        arr[start][size[start]++] = i;
        arr[i][size[i]++] = start;
        cap[start][i] = row[i];
    }
    for(int i=1; i<=N; i++){
        arr[i+50][size[i+50]++] = end;
        arr[end][size[end]++]=i+50;
        cap[i+50][end] = col[i];
    }
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            arr[i][size[i]++] = j+50;
            arr[j+50][size[j+50]++] = i;
        }
    }
    
    l=0, r= 10000;
    m=0;
    int ans;
    while(l<=r){
        m = (l+r)/2;
        if(sum>bfs(m, start, end)) {
            l = m+1;
            
        } 
        else {r = m-1;
        ans = m;}
    }
   
    printf("%d\n", ans);
    bfs(ans, start, end);
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            printf("%d ",flow[i][j+50]);
        }
        printf("\n");
    }
}