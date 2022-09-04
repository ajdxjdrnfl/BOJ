#include <stdio.h>
#include <string.h>
int que[100001];
int visited[100001];
int re[100001];
int rear=-1, front=-1;

void printSoom(int K){
    
    if(re[K]!=K) {
        printSoom(re[K]);
        printf("%d ", re[K]);
    }

}

void soomgo(int N, int K){

    que[++front] = N;
    memset(visited, -1, sizeof(visited));
    visited[N] = 0;
    re[N]=N;
    while(rear<front){
        int temp = que[++rear];

        if(temp==K) break;

        if(temp-1>=0 && visited[temp-1]==-1) {
             que[++front] = temp-1;
             visited[temp-1] = visited[temp]+1;
             re[temp-1] = temp;
        }
        if(temp+1<=100000&& visited[temp+1]==-1){
             que[++front] = temp+1;
             visited[temp+1] = visited[temp]+1;
             re[temp+1] = temp;
        }
        if(temp*2<=100000 && temp>0 && visited[temp*2]==-1) {
            que[++front] = temp*2;
            visited[temp*2] = visited[temp]+1;
            re[temp*2] = temp; 
        }

    }
    

}

int main(void){

    int N,K;
    scanf("%d %d", &N, &K);
    soomgo(N,K);
    printf("%d\n", visited[K]);
    printSoom(K);
    printf("%d\n", K);
}