#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000001


int road[110][110];
int arr[22000][101];
int size[22000];
int cap[22000][10];
int flow[22000][10];
int visited[22000];

int place(int a, int b){
    int i = (a/2)/101;
    int j = (a/2)%101;
    int ii = (b/2)/101;
    int jj = (b/2)%101;

    if(i==ii && jj==j-1) return 0;
    if(i==ii && jj==j+1) return 1;
    if(j==jj && ii==i-1) return 2;
    if(j==jj && ii==i+1) return 3;
    if(i==ii && j==jj) return 4;
}

int min(int a, int b){
    return a<b?a:b;
}

int Dohyun(int start, int end){

    int ans = 0;
    for(int i=0; i<size[start]; i++){
        if(arr[start][i]==end) return -1;
    }
    while(1){
    int que[100001];
    int rear=0, front=0;
    que[front++] = start;
    int c = MAX;
    memset(visited, 0 ,sizeof(visited));
    visited[start] = start;
    while(rear<front){  
        int index = que[rear++];
        for(int i=0; i<size[index]; i++){
            int next = arr[index][i];
            
            if(!visited[next] && cap[index][place(index, next)]-flow[index][place(index, next)]>0){
                visited[next] = index;
                que[front++] = next;
                if(next==end) break;
            }
        }
    }
    if(!visited[end]) break;
    
    for(int i=end; i!=start; i= visited[i]){
         c = min(c, cap[visited[i]][place(visited[i], i)] - flow[visited[i]][place(visited[i], i)]);
    }
    for(int i=end; i!=start; i=visited[i]){
        flow[visited[i]][place(visited[i], i)] += c;
        flow[i][place(i, visited[i])] -= c;
    }
    
    ans+=c;
    
    }
    return ans;
}
int main(void){
    int N,M;
    int start=-1, end=-1;
    memset(road, 0 ,sizeof(road));
    memset(arr, 0, sizeof(arr));
    memset(size, 0 ,sizeof(size));
    memset(cap, 0, sizeof(cap));
    memset(flow, 0 ,sizeof(flow));
   
    scanf("%d %d", &N, &M);
    for(int i=1; i<=N; i++){
        char temp[110];
        scanf("%s", temp);
        for(int j=0; j<M; j++){
            if(temp[j]=='.')  {
                road[i][j+1] = 1;
                int in = (i*101+(j+1))*2;
                int out = in + 1; 
                arr[in][size[in]++] = out;
                arr[out][size[out]++] = in;
                cap[in][4] = 1;
    
            }
            else if(temp[j]=='#') road[i][j+1] = 0;
            else if(temp[j]=='K'){
                start = (i*101+(j+1))*2;
                arr[start][size[start]++] = start+1;
                arr[start+1][size[start+1]++] = start;
                cap[start][4] = 1;
                road[i][j+1] = 1;
                start = start+1;
            }
            else if(temp[j]=='H'){
                road[i][j+1] = 1;
                end = (i*101+(j+1))*2+1;
                arr[end-1][size[end-1]++] = end;
                arr[end][size[end]++] = end-1;
                cap[end-1][4] = 1;
                end = end-1; 
            }
        }
    }

    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            if(road[i][j]){
                int index = i*101+j;
                int in = index*2;
                int out = index*2+1;
                if(j>1 && road[i][j-1]) {
                    arr[out][size[out]++] = (i*101+(j-1))*2;
                    arr[(i*101+(j-1))*2][size[(i*101+(j-1))*2]++] = out;
                    cap[out][0] = MAX;
                }
                if(j<M && road[i][j+1]) {
                    arr[out][size[out]++] = (i*101+(j+1))*2;
                    arr[(i*101+(j+1))*2][size[(i*101+(j+1))*2]++] = out;
                    cap[out][1] = MAX;
                }
                if(i>1 && road[i-1][j]) {
                    arr[out][size[out]++] = ((i-1)*101+j)*2;
                    arr[((i-1)*101+j)*2][size[((i-1)*101+j)*2]++] = out;
                    cap[out][2] = MAX;
                }
                if(i<N && road[i+1][j]) {
                    arr[out][size[out]++] = ((i+1)*101+j)*2;
                    arr[((i+1)*101+j)*2][size[((i+1)*101+j)*2]++] = out;
                    cap[out][3] = MAX;
                }
            }
        }
    }

    
    
    if(start==-1 || end==-1){
        printf("-1\n");
        return 0;
    }
    if(N==1 && M==1){
        printf("-1\n");
        return 0;
    }
    
    printf("%d\n", Dohyun(start, end));
}