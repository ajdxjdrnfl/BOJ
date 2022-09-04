#include <stdio.h>

int stack[100000];
int stackTop=0;
int main(void){
    int K;
    int num;
    int sum=0;
    scanf("%d", &K);
    for(int i=0; i<K; i++){
        scanf("%d", &num);
        if(num!=0) stack[stackTop++] = num;
        else stackTop--;
    }
    for(int i=0; i<stackTop; i++){
        sum+=stack[i];
    }
    printf("%d\n", sum);
}