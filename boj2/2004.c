#include <stdio.h>
long findTwo(long long N){

    long long temp=N;
    long long count=0;
    for(long long i=2; temp/i>=1 ; i*=2){
        count +=temp/i;
    }
    return count;
}
long long findFive(long long N){
    long long temp=N;
    long long count=0;
    for(long long i=5; temp/i>=1 ; i*=5){
        count +=temp/i;
    }
    return count;
}
int main(void){

    long long n,m ,num;
    scanf("%lld %lld", &n, &m);

    long long two=0, five=0;
    two = findTwo(n) - findTwo(n-m)-findTwo(m);
    five = findFive(n) - findFive(n-m)-findFive(m);

    if(two<five) num = two;
    else num = five;
    printf("%lld\n", num);
}