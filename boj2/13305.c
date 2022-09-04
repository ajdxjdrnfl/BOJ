#include<stdio.h>

int main(void){
    int N;
    scanf("%d", &N);
    int dist[N-1], gas[N];
    int temp, disc;
    long long sum = 0;
    for(int i=0; i<N-1; i++){
        scanf("%d", &dist[i]);
    }
    for(int i=0; i<N; i++){
        scanf("%d", &gas[i]);
    }

    for(int i=0; i<N; i++){

        for(int j=i+1; j<N; j++){
            if(gas[i]>gas[j]){
                temp=j-1;
                break;
            }
            if(j==N-1){
                temp=j-1;
                break;
            }
        }
        for(int j=i; j<=temp; j++){
            sum+= (long long)gas[i]*dist[j];
        }
        i=temp;
        if(i==N-2) break;
    }
    printf("%lld\n", sum);
}