#include <stdio.h>
#include <string.h>

int num[20000001];

int main(void){

    int N,M;
    scanf("%d", &N);
    memset(num, 0, sizeof(num));
    for(int i=0; i<N; i++){
        int temp;
        scanf("%d", &temp);
        num[temp+10000000]=1;
    }
    scanf("%d", &M);
    for(int i=0; i<M; i++){
        int temp;
        scanf("%d", &temp);
        printf("%d ", num[temp+10000000]);
    }
    printf("\n");
}