#include <stdio.h>

int arr[1000][1000];
int que[2000000];
int visited[2][1000][1000];
int rear=0, front=0;
int main(void){

    int N,M;
    scanf("%d %d", &N , &M);
    for(int i=0; i<N; i++){
        char temp[1000];
        scanf("%s", temp);
        for(int j=0; j<M ;j++){
            arr[i][j] = temp[j]-'0';
           
        }
    }

    que[front++] = 0;
    visited[0][0][0]=1;
    while(rear<front){
        int temp = que[rear++];
        int i = temp/(M*N);
        int j = (temp-i*M*N)/M;
        int k = (temp-i*M*N)%M;

        if(j==N-1 && k==M-1){
            printf("%d\n", visited[i][j][k]);
            return 0;
        }

        if(i==0){
            if(j+1<N && arr[j+1][k]==1 && visited[i+1][j+1][k]==0){
                que[front++] = (i+1)*M*N + (j+1)*M + k;
                visited[i+1][j+1][k] = visited[i][j][k]+1;
            } 
            if(k+1<M && arr[j][k+1]==1 && visited[i+1][j][k+1]==0){
                que[front++] = (i+1)*M*N + j*M +(k+1);
                visited[i+1][j][k+1] = visited[i][j][k]+1;
            }
            if(j-1>=0 && arr[j-1][k]==1 && visited[i+1][j-1][k]==0){
                que[front++] = (i+1)*M*N +(j-1)*M + k;
                visited[i+1][j-1][k] = visited[i][j][k]+1;
            }
            if(k-1>=0 && arr[j][k-1]==1 && visited[i+1][j][k-1]==0) {
                que[front++] = (i+1)*M*N +j*M + k-1;
                visited[i+1][j][k-1] = visited[i][j][k]+1;
            }
        }
        if(j+1<N && arr[j+1][k]==0 && visited[i][j+1][k]==0){
                que[front++] = (i)*M*N + (j+1)*M + k;
                visited[i][j+1][k] = visited[i][j][k]+1;
            } 
            if(k+1<M && arr[j][k+1]==0 && visited[i][j][k+1]==0){
                que[front++] = (i)*M*N + j*M +(k+1);
                visited[i][j][k+1] = visited[i][j][k]+1;
            }
            if(j-1>=0 && arr[j-1][k]==0 && visited[i][j-1][k]==0){
                que[front++] = (i)*M*N +(j-1)*M + k;
                visited[i][j-1][k] = visited[i][j][k]+1;
            }
            if(k-1>=0 && arr[j][k-1]==0 && visited[i][j][k-1]==0) {
                que[front++] = (i)*M*N +j*M + k-1;
                visited[i][j][k-1] = visited[i][j][k]+1;
            }
    }
    printf("-1\n");
    return 0;

}