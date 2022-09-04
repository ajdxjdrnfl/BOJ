#include <stdio.h>
#define MOD 1000

int main(void){
    int a[5][5];
    int N;
    long long B;
    scanf("%d %lld", &N, &B);
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            scanf("%d", &a[i][j]);
        }
    }

    int temp[5][5];
    int result[5][5];
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            temp[i][j] = a[i][j];
        }
    }
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(i==j) result[i][j] =1;
            else result[i][j] = 0;
        }
    }
    while(B>0){
        if(B%2==1){
        for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            for(int k=0; k<N; k++){
                if(k==0) temp[i][j]=0;
                temp[i][j] = (temp[i][j] + a[i][k]*result[k][j])%MOD; 
            }
        }
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            result[i][j] = temp[i][j];
        }
    }
        }
        B/=2;
        for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            for(int k=0; k<N; k++){
                if(k==0) temp[i][j]=0;
                temp[i][j] = (temp[i][j] + a[i][k]*a[k][j])%MOD; 
            }
        }
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            a[i][j] = temp[i][j];
        }
    }
    }
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}