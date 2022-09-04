#include <stdio.h>

int min(int a, int b){
    if(a<b) return a;
    else return b;
}
int main(void){

    int N,k;
    int ans;
    scanf("%d %d", &N, &k);
    
    int low=1, high=k;

    while(low<=high){
        int mid = (low+high)/2;
        int count=0;

        for(int i=1; i<=N; i++){
            count += min(mid/i, N);
        }

        if(count<k) low = mid+1;
        else {
            ans = mid;
            high = mid-1;
        }
    }
    printf("%d\n", ans);
}