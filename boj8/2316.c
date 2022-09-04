#include <stdio.h>
#include <string.h>

#define MAX 100001

int arr[801][801];
int size[801];
int cap[801][801];
int flow[801][801];
int visited[801];

int min(int a, int b){
    return a<b?a:b;
}
int warhammer(int start, int end){

    int ans = 0;
    while(1){
        int que[100001];
        int rear=0, front=0;
        que[front++] = start;
        int c = MAX;
        memset(visited, 0, sizeof(visited));
        while(rear<front){
            int temp = que[rear++];
            for(int i=0; i<size[temp]; i++){
                int index = arr[temp][i];
                
                if(!visited[index] && (cap[temp][index] - flow[temp][index]>0)){
                    que[front++] = index;
                    visited[index] = temp;
                    if(index==end) break;
                }
            }

        }
        
        if(!visited[end]) break;

        for(int i=end; i!=start; i=visited[i]){
            c = min(c, cap[visited[i]][i] - flow[visited[i]][i]);
        }
        for(int i=end; i!=start; i=visited[i]){
            flow[visited[i]][i]+=c;
            flow[i][visited[i]]-=c;
        }
        ans += c;
    }
    return ans;

}
int main(void){
    int N,P;
    scanf("%d %d", &N, &P);
    memset(arr, 0 ,sizeof(arr));
    memset(size, 0 ,sizeof(size));
    memset(cap, 0 ,sizeof(cap));
    memset(flow, 0, sizeof(flow));
    for(int i=1; i<=N; i++){
        arr[i][size[i]++] = i+400;
        arr[i+400][size[i+400]++] = i;
        cap[i][i+400] = 1;
    }
    
    for(int i=1; i<=P; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        arr[400+a][size[a+400]++] = b;
        arr[b][size[b]++] = a+400;
        arr[b+400][size[b+400]++] = a;
        arr[a][size[a]++] = b+400;
        cap[400+a][b] = 1;
        cap[400+b][a] = 1;        
    }

    printf("%d\n", warhammer(401, 2));
}