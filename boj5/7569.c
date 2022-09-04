#include <stdio.h>

int arr[100][100][100];
int ripe[100][100][100];
int que[1000000];
int rear=0, front=0;

int main(void){

    int M,N,H;
    int cnt=0, total=0;
    scanf("%d %d %d", &M, &N, &H);

    for(int i=0; i<H; i++){
        for(int j=0; j<N; j++){
            for(int k=0; k<M; k++){
                scanf("%d", &arr[i][j][k]);
                if(arr[i][j][k]!=-1) total++;
                if(arr[i][j][k]==1)  {
                    que[front++] = i*M*N + j*M+ k;
                    ripe[i][j][k] = 0;
                }
            }
        }
    }

    while(rear<front){
        cnt++;
        int temp = que[rear++];
        int i = temp/(N*M);
        int j = (temp-i*M*N)/M;
        int k = (temp-i*M*N)%M;
        
        if(cnt==total) {
            printf("%d\n", ripe[i][j][k]);
            break;
        }

        if(i+1<H && arr[i+1][j][k]==0){
            que[front++] =  (i+1)*M*N + j*M +k;
            arr[i+1][j][k] =1;
            ripe[i+1][j][k] = ripe[i][j][k] +1;
        }
        if(i-1>=0 && arr[i-1][j][k]==0){
            que[front++] = (i-1)*M*N + j*M +k;
            arr[i-1][j][k] =1;
            ripe[i-1][j][k] = ripe[i][j][k] +1;
        }
        if(j+1<N && arr[i][j+1][k]==0){
            que[front++] = i*M*N + (j+1)*M +k;
            arr[i][j+1][k] =1;
            ripe[i][j+1][k] = ripe[i][j][k] +1;
        }
        if(j-1>=0 && arr[i][j-1][k]==0){
            que[front++] = i*M*N + (j-1)*M +k;
            arr[i][j-1][k] =1;
            ripe[i][j-1][k] =ripe[i][j][k] +1;
        }
        if(k+1<M && arr[i][j][k+1]==0){
            que[front++] = i*M*N +j*M +k+1;
            arr[i][j][k+1] =1;
            ripe[i][j][k+1] = ripe[i][j][k] +1;
        }
        if(k-1>=0 && arr[i][j][k-1]==0){
            que[front++] = i*M*N +j*M +k-1;
            arr[i][j][k-1] =1;
            ripe[i][j][k-1] = ripe[i][j][k] +1;
        }
    }

    if(cnt!=total) printf("-1\n");
}