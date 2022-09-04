#include <stdio.h>


int main(void){

    int N;
    scanf("%d", &N);
    int arr[N];
    int stack[N];
    int top=-1;
    int result[N];
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }

    for(int i=N-1; i>=0; i--){
        
        while(top!=-1)
        {
            if(stack[top]<=arr[i]){
            top--;
        }
        else if(stack[top]>arr[i]){
            result[i] = stack[top];
            break; 
        }
        }        
    if(top==-1) result[i] = -1;
    stack[++top] = arr[i];
    }
    for(int i=0; i<N; i++){
        printf("%d ", result[i]);
    }
    printf("\n");
    
}