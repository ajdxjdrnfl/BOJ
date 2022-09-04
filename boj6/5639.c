#include <stdio.h>

int pre[10001];

void post(int left, int right){
    if(left>right) return;
    int mid = pre[left];
    int index;
    for(int i=left; i<=right; i++){
        if(pre[i]<=mid) index = i;
        else break;
    }

    post(left+1, index);
    post(index+1, right);
    printf("%d\n" ,mid);

}
int main(void){
    int temp;
    int i=1;

    while(scanf("%d", &temp)!=EOF){
        
        pre[i++] = temp;
        
    }
    post(1, i-1);
}