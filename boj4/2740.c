#include <stdio.h>

int main(void){

    int a[100][100];
    int b[100][100];

    int N,M,K;
    scanf("%d %d", &N, &M);
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            scanf("%d", &a[i][j]);
        }
    }
    scanf("%d %d", &M, &K);
    for(int i=0; i<M; i++){
        for(int j=0; j<K; j++){
            scanf("%d", &b[i][j]);
        }
    }

    int result[100][100]={0,};

    for(int i=0; i<N; i++){
        for(int j=0;  j<K; j++){
            for(int k=0; k<M; k++){
                result[i][j] += a[i][k]*b[k][j];
            }
        }
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<K; j++){
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}