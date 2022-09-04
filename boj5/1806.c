#include <stdio.h>

int arr[100000];

int booboon(int N, int S){
    int left=0;
    int right=0;
    int last=0;
    int smallest=100001;
    int sum=0;
    while(left<=right && right<N){
        sum+=arr[last];
        if(left==right){
            if(arr[left]>=S) return 1;
            else last = ++right;
        }   
        else{
            if(sum>=S){
                if(smallest>right-left+1) smallest = right-left+1;
                sum-=arr[left]; 
                last = ++left;
                sum-=arr[left];
            }
            else last = ++right;
        }
    }
    return smallest;
}
int main(void){
    int N, S;
    scanf("%d %d", &N, &S);
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }
    int result = booboon(N, S);
    if(result==100001) printf("0\n");
    else printf("%d\n", result);
}