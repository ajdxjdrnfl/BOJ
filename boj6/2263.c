#include <stdio.h>

int in[100001];
int post[100001];

void pre(int p_left, int p_right, int left, int right){
    
    if(left>right) return;

    int temp = post[p_right];
    int index=0;
    for(int i=left; i<=right; i++){
        if(temp==in[i]) index = i;
    }
    printf("%d ", temp);
    pre(p_left, p_left+(index-left)-1, left, index-1);
    pre(p_left+(index-left), p_right-1, index+1, right);
}
int main(void){

    int N;
    scanf("%d", &N);
    for(int i=1; i<=N; i++){
        scanf("%d", &in[i]);
    }
    for(int i=1; i<=N; i++){
        scanf("%d", &post[i]);
    }
    
    pre(1, N,1, N);
    
}