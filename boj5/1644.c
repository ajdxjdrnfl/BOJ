#include <stdio.h>
#include <math.h>

#define MAX 4000000
int arr[4000001];
int temp[4000001];
int prime(int N){
   
    if(N==1) return 0;
    
    int size=0;
    
    for(int i=2; i<=sqrt(MAX); i++){
        if(!temp[i]){
        for(int j=2; j<=MAX/i; j++){
            temp[i*j] = 1;
        }   
        }
    }
    
    for(int i=2; i<=N; i++){
        if(!temp[i]) arr[size++] = i;
    }
    int left=0;
    int right=0;
    int sum=0;
    int last=0;
    int result=0;
   
    while(left<=right && right<size){
        sum+=arr[last];
        if(left == right){
            if(sum==N) result++;
            last = ++right;
        }
        else{
            if(sum==N) {
                result++;
                last = ++right;
            }
            else if(sum<N) last = ++right;
            else if(sum>N) {
                sum -= arr[left];
                last = ++left;
                sum -= arr[left];
            }
        }
 
    }
    return result;
}

int main(void){
    int N;
    scanf("%d", &N);
    int result = prime(N);
    printf("%d\n", result);
}