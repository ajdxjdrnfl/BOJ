#include <stdio.h>
#include <string.h>
#define MAX 1001
int num[51][51];
int flow[2610][2610];
int cap[2610][2610];
int visited[2610];
int arr[2610][2610];
int size[2610];

int min(int a, int b){
    return a<b?a:b;
}

int bfs(int start, int end){
    int ans =0;
    while(1){
        int que[100001];
        int rear=0, front=0;
        memset(visited, 0, sizeof(visited));
        int c = 100001;
        que[front++] = start;
    
        while(rear<front){
            int index = que[rear++];
            for(int i=0; i<size[index]; i++){
                int next = arr[index][i];
                if(!visited[next] && cap[index][next] - flow[index][next] >0){
                    que[front++] = next;
                    visited[next] = index;
                    if(next==end) break;
                }
            }
        }
        if(!visited[end]) break;

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
    int T;
    scanf("%d", &T);
    while(T--){
        int n,m;
        int left=0, right=0;

        int start = 2601, end =2602;
        scanf("%d %d", &n ,&m);

        memset(num, 0, sizeof(num));
        memset(flow, 0 ,sizeof(flow));
        memset(cap, 0, sizeof(cap));
        memset(visited, 0, sizeof(visited));
        memset(arr, 0 ,sizeof(arr));
        memset(size, 0, sizeof(size));

        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                scanf("%d", &num[i][j]);
            }
        }

        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                if(i%2==1){
                    if(j%2==1){
                        arr[start][size[start]++] = i*50+j;
                        arr[i*50+j][size[i*50+j]++] = start;
                        cap[start][i*50+j] = num[i][j]; 
                        left += num[i][j];
                    }
                    else{
                        arr[i*50+j][size[i*50+j]++] = end;
                        arr[end][size[end]++] = i*50+j;
                        cap[i*50+j][end] = num[i][j];
                        right += num[i][j];
                    }
                }
                else{
                    if(j%2==1){
                        arr[i*50+j][size[i*50+j]++] = end;
                        arr[end][size[end]++] = i*50+j;
                        cap[i*50+j][end] = num[i][j];
                        right += num[i][j];
                    }
                    else{
                        arr[start][size[start]++] = i*50+j;
                        arr[i*50+j][size[i*50+j]++] = start;
                        cap[start][i*50+j] = num[i][j];
                        left += num[i][j]; 
                    }
                }
            }
        }
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                if((i%2==1 && j%2==1) || (i%2==0 && j%2==0)){
                    int index = i*50+j;
                    if(i>1){
                        arr[index][size[index]++] = (i-1)*50+j;
                        arr[(i-1)*50+j][size[(i-1)*50+j]++] = index;
                        cap[index][(i-1)*50+j] = MAX;
                    }
                    if(i<n){
                        arr[index][size[index]++] = (i+1)*50+j;
                        arr[(i+1)*50+j][size[(i+1)*50+j]++] = index;
                        cap[index][(i+1)*50+j] = MAX;
                    }
                    if(j>1){
                        arr[index][size[index]++] = i*50+(j-1);
                        arr[i*50+(j-1)][size[i*50+(j-1)]++] = index;
                        cap[index][i*50+(j-1)] = MAX;
                    }
                    if(j<m){
                        arr[index][size[index]++] = i*50+(j+1);
                        arr[i*50+(j+1)][size[i*50+(j+1)]++] = index;
                        cap[index][i*50+(j+1)] = MAX;
                    }
                } 
            }
        }
        int ans = bfs(start, end);

        printf("%d\n", left+right-ans);
    }
}