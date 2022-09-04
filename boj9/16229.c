#include <stdio.h>
#include <string.h>

int Z[100010];

void Zalgorithm(char *str, int size){

    Z[0] = size;
    int L=0,R=0;
    for(int i=1; i<size; i++){
        if(i>R){
            L = R = i;
            while(R<size && str[R-L] == str[R]) R++;
            R--;
            Z[i] = R-L+1;
        }
        else{
            int k = i-L;
            if(Z[k] < R-i+1) Z[i] = Z[k];
            else{
                L=i;
                while(R<size && str[R-L] == str[R]) R++;
                R--;
                Z[i] = R-L+1;
            }
        }
    }
}

int min(int a, int b){
    return a<b?a:b;
}

int max(int a, int b){
    return a>b?a:b;
}
int main(void){
    int N, K;
    scanf("%d %d", &N, &K);
    char str[100010];
    scanf("%s", str);
    Zalgorithm(str, N);

    int lar=0;
    for(int i=1; i<N; i++){
        
        if(Z[i]+i == N ) {
            if((i-N%i)%i<=K) lar = max(i, lar);
        }
    }

    
    if(N<=K) printf("%d\n", N);
    else  printf("%d\n", lar);
}