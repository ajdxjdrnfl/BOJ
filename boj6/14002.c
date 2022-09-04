#include <stdio.h>

int arr[1000001];
int dp[1000001];
int re[1000001];
int stack[1000001];
int top=-1;
int top_re=1;

void printRe(int index, int object){
    if(object<0) return;
    for(int i=index; i>=1; i--){
        if(re[i] == object){
            printRe(i-1, object-1);
            printf("%d ", arr[i]);
            break;
        }       
    }
}
int binarySearch(int index, int N){

    int object = arr[index];
    
    int low=0, high=top;
    int mid;
    int ans;
    while(low<=high){
        mid = (low+high)/2;
        if(stack[mid] < object) low = mid+1;
        else if(stack[mid] > object) {
            high = mid-1;
            ans = mid;
        }
        else {
            ans = mid;
            break;
        }
    }
    re[++top_re] = ans;
    stack[ans] = object; 
    return mid;
}

int main(void){
    int N;
    int longest;
    int save;
    scanf("%d", &N);
    for(int i=1; i<=N; i++){
        scanf("%d", &arr[i]);
    }
    stack[++top] = arr[1];
    re[1] = 0;
    for(int i=2; i<=N; i++){
        if(stack[top] < arr[i]) {
            stack[++top] = arr[i];
            re[++top_re] = top;
        }
        else binarySearch(i, N);
    }
    printf("%d\n", top+1);

    printRe(top_re ,top);
    
}