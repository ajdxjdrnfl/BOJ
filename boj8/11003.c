#include <stdio.h>

int A[5000001];
int deque[5000002];
int ind[5000002];
int rear=0, front=0;
int main(void){

    int N,L;
    scanf("%d %d", &N ,&L);
    for(int i=0; i<N; i++){
        scanf("%d", &A[i]);
    }
    deque[front] = A[0];
    ind[front++] = 0;
    printf("%d ", deque[rear]);
    for(int i=1; i<N; i++){
        
        if(rear<front && ind[rear] < i-L+1) rear++;
        
        
        while(1){
            if(rear < front && deque[front-1]>=A[i]) front--;
            else break;
        }
        
        
        deque[front] = A[i];
        ind[front++] = i;
        
        printf("%d ", deque[rear]);
    }
    printf("\n");
}