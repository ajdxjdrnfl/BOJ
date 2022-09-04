#include <stdio.h>
#include <string.h>
int arr[100][100];
int visited[100][100];
int que[10000];
int rear=0, front=0;
int main(void){

    int N, M;
    scanf("%d %d", &N, &M);
    memset(arr, 0, sizeof(arr));
    memset(visited, 0, sizeof(visited));
    for(int i=0; i<N; i++){
        char temp[100];
        scanf("%s", temp);
        for(int j=0; j<M; j++){
            arr[i][j] = temp[j]-'0';
        }

    }

    que[front++]=0;
    visited[0][0] =1;
    while(rear<front){
        int temp = que[rear++];
        int i = temp/M;
        int j = temp%M;
        if(i==N-1 && j==M-1){
            break;
        }
        
        if(j+1<M && arr[i][j+1] == 1 && visited[i][j+1]==0) {
            que[front++]=i*M+(j+1);
            visited[i][j+1] = visited[i][j]+1;
        }
        if(i+1<N && arr[i+1][j] == 1 && visited[i+1][j]==0) {que[front++]=(i+1)*M+j; visited[i+1][j]=visited[i][j]+1;}
        if(j-1>=0 && arr[i][j-1] == 1 && visited[i][j-1]==0){ que[front++]=i*M+(j-1); visited[i][j-1]=visited[i][j]+1;}
        if(i-1>=0 && arr[i-1][j] == 1 && visited[i-1][j]==0) {que[front++]=(i-1)*M+j; visited[i-1][j]=visited[i][j]+1;}
        
    }
    printf("%d\n", visited[N-1][M-1]);
}