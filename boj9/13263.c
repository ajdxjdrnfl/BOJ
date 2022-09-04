#include <stdio.h>
#include <string.h>

typedef long long ll;
typedef struct _line{
    ll co,dp;
    double s;
}line;

ll a[100001];
ll b[100001];
ll dp[100001];

double cross(line a, line b){
    return ((double)(b.dp-a.dp))/((double)(a.co-b.co));
}

int main(void){

    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%lld", &a[i]);
    }
    for(int i=0; i<n; i++){
        scanf("%lld", &b[i]);
    }
    
    memset(dp, 0, sizeof(dp));
    line stack[100001];
    int top=0;

    for(int i=1; i<n; i++){
        line temp;
        temp.co = b[i-1];
        temp.dp = dp[i-1];
        temp.s = 0;
        
        while(top>0){
            temp.s = cross(temp, stack[top-1]);
            if(stack[top-1].s < temp.s) break;
            top--;
        }   
        stack[top++] = temp;
    
        ll x = a[i];
        int low=0, high = top-1;
        int mid=0;
        int ans=0;

        while(low<=high){
            mid = (low+high)/2;
            if(x<stack[mid].s) {
                high = mid-1;
            }
            else {
                ans = mid;
                low = mid+1;
            }
        }
        dp[i] = stack[ans].co*x + stack[ans].dp;                       
    }
    printf("%lld\n", dp[n-1]);
}