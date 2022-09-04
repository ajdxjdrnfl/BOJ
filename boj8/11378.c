#include <stdio.h>
#include <string.h>

#define MAX 1000001

int arr[2005][2005];
int size[2005];
int cap[2005][2005];
int flow[2005][2005];
int visited[2005];

int min(int a, int b){
    return a<b?a:b;
}
int gangho(int start, int end){
    
    int ans=0;
    while(1){
        int f = MAX;
        int que[20005];
        int rear=0, front=0;
        que[front++] = start;
        memset(visited, 0 ,sizeof(visited));
        while(rear<front){
            int index = que[rear++];
            for(int i=0; i<size[index]; i++){
                int temp = arr[index][i];
                if(!visited[temp] && (cap[index][temp] - flow[index][temp] > 0)){
                    visited[temp] = index;
                    que[front++] = temp;
                    if(temp==end) {
                        break;
                    }
                }  
            }
        }
 
        if(!visited[end]) break;
        
        for(int i=end; i!=start; i=visited[i]){
            f = min(f, cap[visited[i]][i] - flow[visited[i]][i]);
        }
        for(int i=end; i!=start; i=visited[i]){
            flow[visited[i]][i]+=f;
            flow[i][visited[i]]-=f;
        } 
        ans+=f;

    }
    return ans;
}
int main(void){

    int N,M,K;
    memset(arr, 0, sizeof(arr));
    memset(size, 0, sizeof(size));
    memset(cap, 0, sizeof(cap));
    memset(flow, 0, sizeof(flow));
    scanf("%d %d %d", &N, &M, &K);
    int start = 2001;
    int end = 2004;
    for(int i=1; i<=N; i++){
        int temp;
        scanf("%d", &temp);
        arr[start+1][size[start+1]++] = i;
        arr[i][size[i]++] = start+1;
        arr[start+2][size[start+2]++] = i;
        arr[i][size[i]++] = start+2;
        cap[start+1][i] = 1;
        cap[start+2][i] = K;
        for(int j=1; j<=temp; j++){
            int a;
            scanf("%d", &a);
            arr[i][size[i]++]= a+1000;
            arr[a+1000][size[a+1000]++] = i;
            cap[i][a+1000] = 1;
        }
    }
    
    arr[start][size[start]++] = start+1;
    arr[start][size[start]++] = start+2;
    arr[start+1][size[start+1]++] = start;
    arr[start+2][size[start+2]++] = start;
    cap[start][start+1] = N;
    cap[start][start+2] = K;

    

    for(int i=1; i<=M; i++){
        arr[i+1000][size[i+1000]++] = end;
        arr[end][size[end]++] = i+1000;
        cap[i+1000][end] = 1;
    }

    printf("%d\n", gangho(start, end));


}