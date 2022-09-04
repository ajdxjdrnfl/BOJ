#include <stdio.h>

int stack[1000000];
int top=-1;

void push(int N){
    stack[++top]=N;
}

int pop(){
    return stack[top--];
}

void binarySearch(int n){
    int low = 0;
    int high = top;
    int ans=0;
    while(low<=high){
        int mid = (low+high)/2;
        if(stack[mid]>n){
            ans = mid;
            high = mid-1;
        }
        else if(stack[mid]==n) return ;
        else low = mid+1;
    }
    stack[ans] = n;
    return ;
}
int main(void){

    int N;
    scanf("%d", &N);
    int arr[N];
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }
    
    push(arr[0]);
    for(int i=1; i<N; i++){
        
        if(stack[top]<arr[i]) push(arr[i]);
        else if(stack[top]>arr[i]) binarySearch(arr[i]);
    }

    printf("%d\n", top+1);
}