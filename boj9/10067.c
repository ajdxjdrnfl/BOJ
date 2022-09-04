#include <stdio.h>
#include <string.h>

#define INF 1000000001
typedef long long ll;

typedef struct _line{
    ll coe, inter;
    double s;
}line;

double cross(line a, line b){
    return ((double)(a.inter-b.inter))/((double)(b.coe-a.coe));
}

ll num[100001];
ll dp[2][100001];
int track[201][100001];
ll sum[100001];

int main(void){

    int n,k;
    scanf("%d %d", &n, &k);
    for(int i=1; i<=n; i++){
        scanf("%lld", &num[i]);
    }
    sum[0] = 0;
    for(int i=1; i<=n; i++){
        sum[i] = sum[i-1] + num[i];
    }
    memset(dp, 0 ,sizeof(dp));
    
    for(int i=1; i<=k; i++){
        line stack[100001];
        int index[100001];
        int top=0;    
        for(int j=1 ; j<=n; j++){
            dp[0][j] = dp[1][j];
        }
        for(int j=i+1; j<=n; j++){
            
            line temp;
            temp.coe = sum[j-1];
            temp.inter = dp[0][j-1] - sum[j-1]*sum[j-1];
            temp.s = -INF;
            while(top>0){
                temp.s = cross(temp, stack[top-1]);
                if(stack[top-1].s < temp.s) break;
                top--;
            }
            stack[top] = temp;
            index[top++] = j-1;
            ll x = sum[j];
            
            int low = 0, high = top-1;
            int mid;
            int ans = 0;
            while(low<=high){
                mid = (low+high)/2;
                if(x < stack[mid].s) high = mid-1;
                else {
                    ans = mid;
                    low = mid+1;
                }
            }
            dp[1][j] = x*stack[ans].coe + stack[ans].inter;
            track[i][j] = index[ans];
        }

    }
    printf("%lld\n", dp[1][n]);
    int stack1[100001];
    int top =0;
    int index1 = track[k][n];
    int temp = 1;
    while(k>temp){
        stack1[top++] = index1;
        index1 = track[k-temp++][index1];
    }
    while(top){
        printf("%d ", stack1[--top]);
    }
    printf("\n");
}