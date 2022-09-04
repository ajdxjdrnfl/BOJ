#include <stdio.h>
#include <string.h>
int que[100000];
int visited[100001];
int rear=0, front=0;

int main(void){
    int N,K;
    scanf("%d %d", &N, &K);

    que[front++] = N;
    memset(visited, -1, sizeof(visited));
    visited[N] = 0;
    while(rear<front){
        int temp = que[rear++];
        if(temp==K){
            printf("%d\n", visited[temp]);
            return 0;
        }
        if(temp+1<=100000 && visited[temp+1]==-1) {
            que[front++] = temp+1;
            visited[temp+1] = visited[temp]+1;
        }
        if(temp-1>=0 && visited[temp-1]==-1){
            que[front++] = temp-1;
            visited[temp-1] = visited[temp]+1;
        }
        if(temp*2<=100000 && visited[temp*2]==-1){
            que[front++] = temp*2;
            visited[temp*2] = visited[temp]+1;
        }
    }    
    
}