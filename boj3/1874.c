#include <stdio.h>
int result[200000];
int resultIndex=0;
int stack[100000];
int top=-1;
void push(int num){
    stack[++top]=num;
    result[resultIndex++]=1;
}
void pop(int num){
    if(top!=-1)
    top--;
    result[resultIndex++]=2;
}
int main(void){
    int N;
    scanf("%d", &N);
    int index=0;
    int arr[N];
    
    int num=1;
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }
    while(1){
        if(num>N+1) break;
        if(index==N) break;
        if(top!=-1){
            if(stack[top]==arr[index]) {
                pop(num);
                index++;
            }
            else if(stack[top]<arr[index]) push(num++);
            else if(stack[top]>arr[index]) {
                break;
            }
        }
        else{
         push(num++);  
        }
    }
    if(top==-1){
        for(int i=0; i<2*N; i++){
            if(result[i]==1) printf("+\n");
            else if(result[i]==2) printf("-\n");
        }
    }
    else{
        printf("NO\n");
    }
}