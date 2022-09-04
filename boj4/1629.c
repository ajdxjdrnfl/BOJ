#include <stdio.h>

int main(void){

    long long A, B,C;
    long long result=1;
    scanf("%d %d %d", &A, &B, &C);

    while(B>0){
        if(B%2==1){
            result = (result*A)%C;
        }
        B/=2;
        A=(A*A)%C;
    }
    printf("%lld\n", result);
}