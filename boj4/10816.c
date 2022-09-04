#include <stdio.h>

int ind[20000001]={0,};
int main(void){

    int num1, num2;

    scanf("%d", &num1);
    int N[num1];
    for(int i=0; i<num1; i++){
        scanf("%d", &N[i]);
        ind[10000000+N[i]]++;
    }    
    scanf("%d", &num2);
    int M[num2];
    for(int i=0; i<num2; i++){
        scanf("%d", &M[i]);
    }
    for(int i=0; i<num2; i++){
        printf("%d ", ind[M[i]+10000000]);
    }
    printf("\n");
}