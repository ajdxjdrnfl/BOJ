#include <stdio.h>

long long stack[100000]={0};
int top = -1;   
int ind[100000];
long long pop(){
    return stack[top--];
}

void push(long long num, int temp){
    stack[++top] = num;
    ind[top] = temp;
}
long long solve(long long * h, int n){
    long long result = -1;
    long long temp;
    int i = 0;
    while(i<n){
        if(top==-1) {
            push(h[i], i);
            }
        
        else if(stack[top] < h[i]) {
            push(h[i], i);
            
        }
        
        else if(stack[top] > h[i]) {
            long long tmp = h[i];
            while(tmp<stack[top] && top!=-1){
                temp = pop();
                if(result < temp * (i-ind[top+1])) result = temp*(i-ind[top+1]);
                
            }
            push(h[i], ind[top+1]);
        }    
     
     i++;
    }

    while(top!=-1){
        temp = pop();
        if(result < temp * (n-ind[top+1])) result = temp*(n-ind[top+1]);
        
    }

    return result;
}
int main(void){

    int n;
    scanf("%d", &n);
   
    
    while(n!=0){
         long long h[n];
        for(int i=0; i<n; i++){
            scanf("%lld", &h[i]);
        }
        printf("%lld\n",solve(h, n));
        scanf("%d", &n);
        
    }


}