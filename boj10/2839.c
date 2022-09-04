#include <stdio.h>

int main(void){

    int N;
    scanf("%d", &N);
    int Q = N/5;
    if(N%5==0){
        printf("%d\n", Q);
    }
    else if(N%5==1){
        if(Q>=1) printf("%d\n", Q+1);
        else printf("-1\n");
    }
    else if(N%5==2){
        if(Q>=2) printf("%d\n", Q+2);
        else printf("-1\n");
    }
    else if(N%5==3){
        printf("%d\n", Q+1);
    }
    else if(N%5==4){
        if(Q>=1)printf("%d\n", Q+2);
        else printf("-1\n");
    }
}