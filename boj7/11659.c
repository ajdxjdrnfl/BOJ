#include <stdio.h>


int arr[100001];
int sum[100001];
int main(void){
    int N, M;
    scanf("%d %d", &N, &M);
    sum[0] = 0;
    for(int i=1; i<=N; i++){
        scanf("%d", &arr[i]);
        sum[i] = sum[i-1] + arr[i];
    }
    for(int i=0; i<M; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        printf("%d\n", sum[b] - sum[a]+arr[a]);
    }
}