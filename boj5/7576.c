#include <stdio.h>

int ripe[1000][1000];
int que[1000000];
int rear=0, front=0;
int arr[1000][1000];
int main(void){

    int M, N;
    int cnt=0, total=0;
    scanf("%d %d", &N, &M);
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            scanf("%d", &arr[i][j]);
            if(arr[i][j]!=-1) total++;
            if(arr[i][j]==1) {que[front++]=i*N+j; ripe[i][j]=0;}
        }
    }
  
    while(rear<front){
        cnt++;
        int temp =que[rear++];
        int i = temp/N;
        int j = temp%N;

        if(cnt==total) {
            
            printf("%d\n", ripe[i][j]);
            return 0;
        }
        if(i+1<M && arr[i+1][j]==0) {que[front++] = (i+1)*N+j; arr[i+1][j]=1; ripe[i+1][j]=ripe[i][j]+1;}
        if(j+1<N && arr[i][j+1]==0) {que[front++] = i*N+(j+1); arr[i][j+1]=1; ripe[i][j+1]=ripe[i][j]+1;}
        if(i-1>=0 && arr[i-1][j]==0) {que[front++] = (i-1)*N+j; arr[i-1][j]=1; ripe[i-1][j]=ripe[i][j]+1;}
        if(j-1>=0 && arr[i][j-1]==0) {que[front++] = i*N+j-1; arr[i][j-1]=1; ripe[i][j-1]=ripe[i][j]+1;}  
    }
    
    printf("%d\n", -1);
    return 0;
}