#include <stdio.h>

long long factorial(int n){
    if(n==1) return 1;

    return n*factorial(n-1);
}
int main(void){
    int N;
    long long result;
    int two=0, five=0;
    int num=0;
    long long temp;
    scanf("%d", &N);
    for(int i=N; i>=1; i--){
        temp = i;
        while(temp%2==0){
            two++;
            temp = temp/2;
        }
        while(temp%5==0){
            five++;
            temp = temp/5;
        }
    }

    if(two<five) num = two;
    else num = five;
   
    printf("%d\n", num);
}